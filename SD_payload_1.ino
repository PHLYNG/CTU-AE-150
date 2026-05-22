#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <RTClib.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_ADXL345_U.h>
#include <MS5611.h>

// --- HARDWARE CONSTANTS ---
const int chipSelect = 5;

char filename[20];
float launchPadPressure; // Will be stored in Pascals

// --- SENSOR OBJECTS ---
RTC_DS3231 rtc;
Adafruit_AHTX0 aht;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
MS5611 ms5611;

// --- DEFENSIVE STATUS FLAGS ---
bool rtcOk = false, ahtOk = false, accelOk = false, msOk = false;

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
    Serial.println("[OK] RTC Online");
  } else {
    Serial.println("[FAIL] RTC Offline");
  }

  // 2. SD CARD (Critical Fail)
  if (!SD.begin(chipSelect)) {
    Serial.println("CRITICAL FAIL: SD Card");
    while (1); // Halt execution if SD fails
  }

  int fileCount = 0;
  sprintf(filename, "/log%d.csv", fileCount);
  while (SD.exists(filename)) { 
    sprintf(filename, "/log%d.csv", ++fileCount); 
  }
  Serial.printf("File: %s\n", filename);

  // 3. SENSOR INIT & CALIBRATION
  if (aht.begin()) {
    ahtOk = true;
    Serial.println("[OK] AHT20 Online");
  } else {
    Serial.println("[FAIL] AHT20 Offline");
  }

  if (accel.begin()) {
    accelOk = true;
    accel.setRange(ADXL345_RANGE_16_G); // Best for high dynamic environments
    Serial.println("[OK] ADXL345 Online");
  } else {
    Serial.println("[FAIL] ADXL345 Offline");
  }

  if (ms5611.begin()) {
    msOk = true;
    float totalP = 0;
    for(int i = 0; i < 5; i++) { 
      ms5611.read();
      totalP += (ms5611.getPressure() * 100.0); 
      delay(50); 
    }
    launchPadPressure = totalP / 5.0;
    Serial.println("[OK] MS5611 Online");
  } else {
    Serial.println("[FAIL] MS5611 Offline");
  }

  // 4. HEADER WRITING
  File dataFile = SD.open(filename, FILE_WRITE);
  if (dataFile) {
    dataFile.println("Millis,Time,Temp_C,Humidity_%,Press_Pa,Alt_m,AccelX_ms2,AccelY_ms2,AccelZ_ms2");
    dataFile.close();
  }
}

void loop() {
  // Declare variables at the top of the loop so the logger can see them all
  float temp = -999, humidity = -999, press = 0, alt = -999;
  float ax = 0, ay = 0, az = 0;
  String timeStr = "00:00:00";

  // --- A. HUMIDITY ONLY (AHT20) ---
  if (ahtOk) {
    sensors_event_t aht_humidity, aht_temp;
    aht.getEvent(&aht_humidity, &aht_temp); 
    humidity = aht_humidity.relative_humidity;
  }

  // --- B. KINEMATIC DATA (ADXL345) ---
  if (accelOk) {
    sensors_event_t event;
    accel.getEvent(&event);
    ax = event.acceleration.x;
    ay = event.acceleration.y;
    az = event.acceleration.z;
  }

  // --- C. PRESSURE, ALTITUDE, & TEMPERATURE (MS5611) ---
  if (msOk) {
    ms5611.read(); 
    temp = ms5611.getTemperature(); 
    press = ms5611.getPressure() * 100.0; 
    
    if (launchPadPressure > 0) {
      alt = 44330.0 * (1.0 - pow(press / launchPadPressure, 0.1903));
    }
  }

  // --- D. TIME ---
  if (rtcOk) {
    DateTime now = rtc.now();
    char buf[10];
    sprintf(buf, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
    timeStr = String(buf);
  }

  // --- E. LOGGING ---
  String dataLine = String(millis()) + "," + timeStr + "," + 
                    String(temp) + "," + String(humidity) + "," + 
                    String(press) + "," + String(alt) + "," +
                    String(ax) + "," + String(ay) + "," + String(az);

  File dataFile = SD.open(filename, FILE_APPEND); 
  if (dataFile) {
    dataFile.println(dataLine);
    dataFile.close();
    Serial.print("LOGGED: "); Serial.println(dataLine);
  } else {
    Serial.println("!! SD ERROR !!");
  }

  delay(250);
}
