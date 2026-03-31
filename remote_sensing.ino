#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_BNO055.h>
#include "DFRobot_AirQualitySensor.h"

// SD Card Pin
#define SD_CS 5

// Standard Sea Level Pressure (1013.25 hPa = 101325 Pa)
// For better accuracy, look up the current "Altimeter Setting" for Baltimore
#define SEA_LEVEL_PRESSURE 101325 

Adafruit_BMP085 bmp;
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);
DFRobot_AirQualitySensor particle(&Wire, 0x19);

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  if (!bmp.begin(0x77)) { Serial.println("BMP085 missing!"); }
  if (!bno.begin()) { Serial.println("BNO055 missing!"); while (1); }
  while (particle.begin() != 0) { Serial.println("SEN0460 missing!"); delay(1000); }
  if (!SD.begin(SD_CS)) { Serial.println("SD failed!"); while (1); }

  // Updated CSV header with Pressure and Altitude
  File dataFile = SD.open("/data.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println("Time_ms,Temp_C,Pressure_Pa,Altitude_m,Heading,Pitch,Roll,PM1_0,PM2_5,PM10");
    dataFile.close();
    Serial.println("Header initialized.");
  }

  bno.setExtCrystalUse(true);
}

void loop() {
  sensors_event_t event;
  bno.getEvent(&event);

  unsigned long now = millis();
  float temp = bmp.readTemperature();
  float pressure = bmp.readPressure(); // Pressure in Pascals
  float altitude = bmp.readAltitude(SEA_LEVEL_PRESSURE); // Altitude in Meters

  uint16_t pm1_0 = particle.gainParticleConcentration_ugm3(PARTICLE_PM1_0_STANDARD);
  uint16_t pm2_5 = particle.gainParticleConcentration_ugm3(PARTICLE_PM2_5_STANDARD);
  uint16_t pm10  = particle.gainParticleConcentration_ugm3(PARTICLE_PM10_STANDARD);

  // Build the expanded data string
  String dataString = String(now) + "," + 
                      String(temp) + "," + 
                      String(pressure) + "," + 
                      String(altitude) + "," + 
                      String(event.orientation.x) + "," + 
                      String(event.orientation.y) + "," + 
                      String(event.orientation.z) + "," +
                      String(pm1_0) + "," +
                      String(pm2_5) + "," +
                      String(pm10);

  File dataFile = SD.open("/data.csv", FILE_APPEND);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    Serial.println(dataString); 
  } else {
    Serial.println("SD Error!");
  }

  delay(200); 
}
