#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <RTClib.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <DFRobot_AirQualitySensor.h>

// --- VOLUMETRIC CONSTANTS ---
const int chipSelect = 5;
const float CAVITY_VOLUME_L = 0.972; // 972,000 mm^3 = 0.972 L
const float SENSOR_BASE_VOL = 0.1;   // Sensor counts per 0.1L
const float VOL_MULTIPLIER = CAVITY_VOLUME_L / SENSOR_BASE_VOL; // 9.72

char filename[20];
float launchPadPressure;

RTC_DS3231 rtc;
Adafruit_BMP085 bmp;
Adafruit_BNO055 bno = Adafruit_BNO055(55);
DFRobot_AirQualitySensor airQuality(&Wire);

// Defensive Status Flags
bool rtcOk = false, bmpOk = false, bnoOk = false, airOk = false;

void setup() {
  Serial.begin(115200);
  unsigned long startWait = millis();
  while (!Serial && millis() - startWait < 3000);

  Serial.println("\n--- FULL MISSION INITIALIZATION ---");
  Wire.begin();
  Wire.setTimeOut(50); // Prevent I2C lockups

  // 1. RTC SYNC
  if (rtc.begin()) {
    rtcOk = true;
    if (rtc.lostPower()) rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // 2. SD CARD (Critical Fail)
  if (!SD.begin(chipSelect)) {
    Serial.println("CRITICAL FAIL: SD Card");
    while (1);
  }

  int fileCount = 0;
  sprintf(filename, "/log%d.csv", fileCount);
  while (SD.exists(filename)) { sprintf(filename, "/log%d.csv", ++fileCount); }
  Serial.printf("File: %s\n", filename);

  // 3. SENSOR INIT & CALIBRATION
  if (bmp.begin()) {
    bmpOk = true;
    float totalP = 0;
    for(int i=0; i<5; i++) { totalP += bmp.readPressure(); delay(50); }
    launchPadPressure = totalP / 5.0;
    Serial.println("[OK] BMP085 Online");
  }

  if (bno.begin()) {
    bnoOk = true;
    Serial.println("[OK] BNO055 Online");
  }

  if (airQuality.begin()) {
    airOk = true;
    Serial.println("[OK] Air Quality Online");
  }

  // 4. HEADER WRITING
  File dataFile = SD.open(filename, FILE_WRITE);
  if (dataFile) {
    dataFile.println("Millis,Time,Temp_C,Press_Pa,Alt_m,Yaw,Pitch,Roll,PM2.5_Conc,PM10_Conc,Cavity_Total_Particles,Cavity_Mass_ug,Bin0.3,Bin0.5,Bin1.0,Bin2.5,Bin5.0,Bin10");
    dataFile.close();
  }
}

void loop() {
  // --- A. ENVIRONMENTAL DATA (BMP085) ---
  float temp = -999, alt = -999;
  int32_t press = 0;
  if (bmpOk) {
    temp = bmp.readTemperature();
    press = bmp.readPressure();
    alt = bmp.readAltitude(launchPadPressure);
  }

  // --- B. ORIENTATION DATA (BNO055) ---
  sensors_event_t event;
  float yaw = 0, pitch = 0, roll = 0;
  if (bnoOk) {
    bno.getEvent(&event);
    yaw = event.orientation.x;
    pitch = event.orientation.y;
    roll = event.orientation.z;
  }

  // --- C. ADVANCED AIR QUALITY DATA ---
  uint16_t c0_3=0, c0_5=0, c1_0=0, c2_5=0, c5_0=0, c10=0;
  uint16_t pm25_conc=0, pm10_conc=0;
  float cavityTotalParticles = 0;
  // absolute count of particles sensor has counted
  float cavityTotalMass_ug = 0;
  // mass of particles being counted inside the payload cavity

  if (airOk) {
    pm25_conc = airQuality.gainParticleConcentration_ugm3(PARTICLE_PM2_5_STANDARD);
    pm10_conc = airQuality.gainParticleConcentration_ugm3(PARTICLE_PM10_STANDARD);
    c0_3 = airQuality.gainParticleNum_Every0_1L(PARTICLENUM_0_3_UM_EVERY0_1L_AIR);
    c0_5 = airQuality.gainParticleNum_Every0_1L(PARTICLENUM_0_5_UM_EVERY0_1L_AIR);
    c1_0 = airQuality.gainParticleNum_Every0_1L(PARTICLENUM_1_0_UM_EVERY0_1L_AIR);
    c2_5 = airQuality.gainParticleNum_Every0_1L(PARTICLENUM_2_5_UM_EVERY0_1L_AIR);
    c5_0 = airQuality.gainParticleNum_Every0_1L(PARTICLENUM_5_0_UM_EVERY0_1L_AIR);
    c10  = airQuality.gainParticleNum_Every0_1L(PARTICLENUM_10_UM_EVERY0_1L_AIR);

    // Absolute count in the 0.972L cavity
    uint32_t totalRaw = (uint32_t)c0_3 + c0_5 + c1_0 + c2_5 + c5_0 + c10;
    cavityTotalParticles = totalRaw * VOL_MULTIPLIER;

    // Total Mass in 0.972L (Conc * Volume in m3)
    cavityTotalMass_ug = (float)pm10_conc * 0.000972;
  }

  // --- D. TIME ---
  String timeStr = "00:00:00";
  if (rtcOk) {
    DateTime now = rtc.now();
    char buf[10];
    sprintf(buf, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
    timeStr = String(buf);
  }

  // --- E. LOGGING ---
  String dataLine = String(millis()) + "," + timeStr + "," + 
                    String(temp) + "," + String(press) + "," + String(alt) + "," +
                    String(yaw) + "," + String(pitch) + "," + String(roll) + "," +
                    String(pm25_conc) + "," + String(pm10_conc) + "," + 
                    String(cavityTotalParticles) + "," + String(cavityTotalMass_ug) + "," +
                    String(c0_3) + "," + String(c0_5) + "," + String(c1_0) + "," + 
                    String(c2_5) + "," + String(c5_0) + "," + String(c10);

  File dataFile = SD.open(filename, FILE_APPEND);
  if (dataFile) {
    dataFile.println(dataLine);
    dataFile.close();
    Serial.print("LOGGED: "); Serial.println(dataLine);
  } else {
    Serial.println("!! SD ERROR !!");
  }

  delay(2000);
}
