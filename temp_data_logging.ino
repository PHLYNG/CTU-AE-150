#include <SPI.h>
#include <SD.h>
#include <Adafruit_BMP085.h>

// PIN CONFIGURATION
const int chipSelect = 10; // Ensure this matches your wiring
Adafruit_BMP085 bmp;

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for Serial Monitor

  Serial.println("Initializing System...");

  // 1. Initialize BMP085
  if (!bmp.begin()) {
    Serial.println("Could not find BMP085. Check wiring (Pins 20/21)!");
    while (1);
  }

  // 2. Initialize SD Card
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("SD initialization failed! Check wiring (Pins 50-52).");
    return; // Don't proceed if SD fails
  }
  Serial.println("SD initialization done.");

  // Create Header for CSV file if it doesn't exist
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println("Temp(C),Pressure(Pa),Altitude(m)");
    dataFile.close();
  }
}

void loop() {
  // Read sensor data
  float temp = bmp.readTemperature();
  int32_t press = bmp.readPressure();
  float alt = bmp.readAltitude();

  // Create a comma-separated string
  String dataString = String(temp) + "," + String(press) + "," + String(alt);

  // Log to SD Card
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    
    // Also print to Serial for debugging
    Serial.print("Logged: ");
    Serial.println(dataString);
  } else {
    Serial.println("Error opening datalog.txt");
  }

  delay(2000); // Log every 2 seconds
}
