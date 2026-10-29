# Materials

## Sensor Package

The sensor package for this payload are basic but they are, either altogether or some combination of, the foundation of any complex payload project you might create later on.

1. [Real Time Clock - DS3231](https://a.co/d/0bGsMs1b)
2. [Temperature and Pressure - MS5611](https://a.co/d/01ImdkOY)
3. [Inertial Measurement Unit - GY-521](https://a.co/d/0gLBPZdt)
4. [SD Card Reader](https://a.co/d/002QuOu7)

If all you fly in your payload is this sensor package, you will still learn a lot.

The Real Time Clock (RTC) and MS5611 both are a means of correlating scientific data your payload might be collecting. For example, x seconds into the flight, y data was collected. Alternatively you could say at x altitude (determined by converting pressure readings), y data was collected.

The Inertial Measurement Unit (IMU) can tell you how your payload is oriented throughout the flight. That could be important if you have a sensor that requires an orientation that is perpendicular to the Earth's surface as the payload is rising.

![img alt](https://github.com/PHLYNG/CTU-AE-150/blob/f84b2b25b0527a2344d09eb8b14be9175b818866/images/Screenshot%202026-10-23%20145406.png)

## Basic Materials

Next section: [Command & Data Handling (CDH)](Microcontroller.md)
