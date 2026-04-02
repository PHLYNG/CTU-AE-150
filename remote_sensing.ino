#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <RTClib.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <DFRobot_AirQualitySensor.h>

const int chipSelect = 5;
char filename[20]; 

// This will store the pressure at your launch site
float launchPadPressure; 

RTC_DS3231 rtc;
Adafruit_BMP085 bmp;
Adafruit_BNO055 bno = Adafruit_BNO055(55);
DFRobot_AirQualitySensor airQuality(&Wire);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(1000); 

  Serial.println("\n--- HAB PAYLOAD INITIALIZATION ---");

  if (!SD.begin(chipSelect)) {
    Serial.println("CRITICAL FAIL: SD Card");
    while (1); 
  }

  // Filename Auto-Increment
  int fileCount = 0;
  sprintf(filename, "/log%d.csv", fileCount);
  while (SD.exists(filename)) {
    fileCount++;
    sprintf(filename, "/log%d.csv", fileCount);
  }

  if (!rtc.begin()) Serial.println("FAIL: RTC");
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Uncomment to sync once

  if (!bmp.begin()) {
    Serial.println("FAIL: BMP085");
  } else {
    // --- CALIBRATION STEP ---
    // Take 5 readings and average them to get a stable "Ground Zero" pressure
    float totalP = 0;
    for(int i=0; i<5; i++) {
      totalP += bmp.readPressure();
      delay(100);
    }
    launchPadPressure = totalP / 5.0;
    Serial.print("PASS: BMP085 Calibrated. Ground Pressure: "); 
    Serial.print(launchPadPressure); Serial.println(" Pa");
  }

  if (!bno.begin()) Serial.println("FAIL: BNO055");
  if (!airQuality.begin()) Serial.println("FAIL: SEN0460");

  File dataFile = SD.open(filename, FILE_WRITE);
  if (dataFile) {
    dataFile.println("Year,Month,Day,Hour,Min,Sec,Temp_C,Press_Pa,Alt_AGL_m,Yaw,Pitch,Roll,PM2_5_ug,PM10_ug,Count_2_5_to_10");
    dataFile.close();
  }
  
  Serial.println("--- LOGGING AGL ALTITUDE ---");
}

void loop() {
  DateTime now = rtc.now();

  float temp = bmp.readTemperature();
  int32_t pressure = bmp.readPressure();
  
  // Calculate altitude relative to your specific launch site
  float altitudeAGL = bmp.readAltitude(launchPadPressure);

  sensors_event_t event;
  bno.getEvent(&event);

  uint16_t pm25_conc = airQuality.gainParticleConcentration_ugm3(PARTICLE_PM2_5_STANDARD);
  uint16_t pm10_conc = airQuality.gainParticleConcentration_ugm3(PARTICLE_PM10_STANDARD);
  
  uint16_t gt2_5 = airQuality.gainParticleNum_Every0_1L(PARTICLENUM_2_5_UM_EVERY0_1L_AIR);
  uint16_t gt10  = airQuality.gainParticleNum_Every0_1L(PARTICLENUM_10_UM_EVERY0_1L_AIR);
  uint16_t count_2_5_to_10 = (gt2_5 > gt10) ? (gt2_5 - gt10) : 0;

  File dataFile = SD.open(filename, FILE_APPEND);
  if (dataFile) {
    dataFile.printf("%d,%d,%d,%d,%d,%d,", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
    dataFile.printf("%.2f,%ld,%.2f,%.2f,%.2f,%.2f,%d,%d,%d\n", 
                    temp, pressure, altitudeAGL, event.orientation.x, event.orientation.y, event.orientation.z, 
                    pm25_conc, pm10_conc, count_2_5_to_10);
    dataFile.close();
  }

  // --- FULL DEBUG OUTPUT ---
  Serial.print(now.timestamp(DateTime::TIMESTAMP_TIME));
  Serial.printf(" | Alt: %.1fm | Temp: %.1fC | P: %ldPa | YPR: %.1f,%.1f,%.1f | PM10: %d\n", 
                altitudeAGL, temp, pressure, event.orientation.x, event.orientation.y, event.orientation.z, pm10_conc);

  delay(2000); 
}
