# Sensor Package

The sensor package for this payload are basic but they are, either altogether or some combination of, the foundation of any complex payload project you might create later on.

1. [Real Time Clock - DS3231](https://a.co/d/0bGsMs1b)
2. [Temperature and Pressure - MS5611](https://a.co/d/01ImdkOY)
3. [Inertial Measurement Unit - GY-521](https://a.co/d/0gLBPZdt)
4. [SD Card Reader](https://a.co/d/002QuOu7)

If all you fly in your payload is this sensor package, you will still learn a lot.

The Real Time Clock (RTC) and MS5611 both are a means of correlating scientific data your payload might be collecting. For example, x seconds into the flight, y data was collected. Alternatively you could say at x altitude (determined by converting pressure readings), y data was collected.

The Inertial Measurement Unit (IMU) can tell you how your payload is oriented throughout the flight. That could be important if you have a sensor that requires an orientation that is perpendicular to the Earth's surface as the payload is rising.

![img alt](https://github.com/PHLYNG/CTU-AE-150/blob/f84b2b25b0527a2344d09eb8b14be9175b818866/images/Screenshot%202026-10-23%20145406.png)

Before getting fully underway with prototyping, a good first step is to connect each individual sensor to the ESP32 and run sample code to ensure that your sensors are functioning.

After following the steps in the Command & Data Handling section of this Manual and while the ESP32 is connected to your computer, follow these steps to test your sensors one by one. This Manual will proceed with the RTC as an example, but the steps will be the same for the other sensors.

Please note that you may need to solder pin headers to your sensors. Head over to the [Soldering](Soldering.md) section for tips and tutorials.

  1. Connect a jumper cable to the 3.3V pin on the ESP32 and then connect the other end to the VCC pin on the sensor
  2. Connect a jumper cable to the GND pin on the ESP32 and then connect the other end to the GND pin on the sensor
     - It is good practice to use red for power and black for ground
  4. Connect a jumper cable to the 22 pin on the ESP32 and then connect the other end to the SCL pin on the sensor
  5. Connect a jumper cable to the 21 pin on the ESP32 and then connect the other end to the SDA pin on the sensor
     - If you look back at the ESP32 diagram in the CDH section, you will see that pins 21 and 22 are labeled SDA and SCL, respectively
  7. When completed, your ESP32 and connected sensor should look like this:
     - [insert a picture of a single sensor connected to the ESP32] 
  8. In the Arduino IDE, select the Library Manager icon
     - ![image alt](https://github.com/PHLYNG/CTU-AE-150/blob/1f0a11a02f1457941f0e2fc2d92e6f2c6467ca44/images/Screenshot%202026-10-23%20173251.png)
  9. In the search bar that appears, search for the sensor that you have connected to your ESP32
  10. From the results, choose an official library (Adafruit, Sparkfun, Arduino, etc) if available
      - If an official library is not available, feel free to search the internet for which library might be the best for your particular option
      - Otherwise, choosing the first available option should suffice
      - ![image alt](https://github.com/PHLYNG/CTU-AE-150/blob/1f0a11a02f1457941f0e2fc2d92e6f2c6467ca44/images/Screenshot%202026-10-23%20172345.png)
  11. When installing a Library package, a popup may appear saying that the Library you're trying to install requires other dependencies that are currently not installed; if that occurs, simply click "INSTALL ALL".
  12. Click File in the top left corner of the Arduino IDE, then hover over Examples from the drop down menu, then select
  13. [Need to go through this process myself to get the sequencing correct]

If the sensor is working properly, you will see data populating the Arduino IDE console.

In order to ensure that the data being produced is correct we must calibrate our sensors, which will be discussed in the following section.

Next section: [Calibration](Calibration.md)
