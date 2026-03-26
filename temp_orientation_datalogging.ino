#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_BNO055.h>

// Pins for the Elegoo ESP32
#define SD_CS 5

Adafruit_BMP085 bmp;
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  // Initialize BMP085
  if (!bmp.begin(0x77)) {
    Serial.println("BMP085 missing!");
  }

  // Initialize BNO055
  if (!bno.begin()) {
    Serial.println("BNO055 missing!");
    while (1);
  }

  // Initialize SD
  if (!SD.begin(SD_CS)) {
    Serial.println("SD initialization failed!");
    while (1);
  }

  // Create the CSV header for MATLAB
  File dataFile = SD.open("/data.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println("Time_ms,Temp_C,Heading,Pitch,Roll");
    dataFile.close();
    Serial.println("File created with headers.");
  }

  bno.setExtCrystalUse(true);
  Serial.println("System online. Logging started...");
}

void loop() {
  sensors_event_t event;
  bno.getEvent(&event);

  float temp = bmp.readTemperature();
  unsigned long now = millis();

  // Create the comma-separated string
  String dataString = String(now) + "," + 
                      String(temp) + "," + 
                      String(event.orientation.x) + "," + 
                      String(event.orientation.y) + "," + 
                      String(event.orientation.z);

  // Write to SD card
  File dataFile = SD.open("/data.csv", FILE_APPEND);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // Also print to Serial so you can monitor live
    Serial.println(dataString);
  } else {
    Serial.println("Error writing to SD!");
  }

  delay(100); // Logs at 10Hz (10 times per second)
}
