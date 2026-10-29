# Integration

Once each sensor is powered on and confirmed to be functioning properly, connect everything together into a single circuit.

## Prototyping - Initial Assembly on Solderless Breadboards

Before assembling a permanent soldered board or perfboard, all components should first be wired using solderless breadboards.

Two major advantages of using breadboards:

  1. A breadboard allows components, power distribution lines, and signal jumpers to be rearranged dynamically without desoldering or damaging delicate board pads.
  2. Prototyping on a breadboard makes early wiring errors, such as landing a jumper cable on the wrong pin or misrouting a digital bus line, completely reversible and low stakes. Mistakes can be caught and corrected immediately during pre-assembly bench testing before any permanent soldering takes place.

Here is a diagram of how a breadboard works:

![image alt](https://github.com/PHLYNG/HAB-CINT/blob/cbf6dc40e3856e4c5aac83eab86c16e7c659f563/images/breadboard-illustrated.adb3be7b.jpg)
Image source: https://dev.blues.io/blog/blues-university-first-components-breadboard/

When insert the pins of a component into the breadboard, you want the pins running horizontally (where the diagram says "Not connected together"). 

Note that all three sensors in the sensor package have the same VCC, GND, SDA, and SCL pins.

Once you place the 3 sensors on the breadboard, you can connect each sensor's SDA pin (for example) with a jumper cable on one end into a vertical column (where the diagram says "Connected together") with the other end. By doing so, you can connect the ESP32's SDA pin (pin 21) into that same column and thus all the sensor's SDA output data will feed into a single SDA pin on the ESP32.

This principle applies also for the SCL pin.

Another way this concept plays out is with power and ground. The ESP32 can power the "rails" of the breadboard. By connect the ESP32's 3v3 pin to one of the rails, each sensor can then connect to the same power rail to receive power. The same goes for ground. Note that the rails on either end of the breadboard are not connected together unless explicitly connected with a jumper cable. Go ahead and try this by connecting the two ground rails together with a jumper cable. This will come in handy in a moment.

## SD Card Reader

Now we can finally introduce the SD Card Reader into the circuit. This component needs to be connected to the 5V pin on the ESP32 because it has current requirements that are greater than the sensors. If these requirements aren't met the SD Card Reader may not spin up when the payload is powered on, or it may drop in and out resulting in inconsistent data logging if not a total loss in data logging.

You will need to connect the ESP32's VIN (5V) pin to the breadboard rail opposite to the rail that is powering the sensors. Connect the SD Card Reader's VCC pin to the 5V rail. Because this rail is connected across the breadboard as mentioned before, you can also connect the Reader's GND pin to the same rail for tidiness.

The SD Card Reader, instead of SDA and SCL pins, has MISO and MOSI pins. These pins need to connect to pins 19 and 23 on the ESP32 respectively.

The end result should look something like this:

![image alt](https://github.com/PHLYNG/HAB-CINT/blob/8a8657c83d32f21084fcae816d20b478ab925065/images/PXL_20261029_184732134.jpg)

Note that tidiness is critical! Having jumper cables of different lengths and colors helps with this. Establishing conventions, even if only for yourself, for what colors go with what pins is also helpful for keeping track of things and debugging if you run into any issues.

## Code

One of the few things this Guide will not fully walk through is how to write the code for your integrated circuit.

A good place to start is to go through the installed sensor libraries and find sample code that has outputs that you like and then combine everything together.

This is an area where one size will not fit all. Each individual user may want to see their data logged in a different way, or give more weight to certain data types over others. Even though the sensor package is the same the bugs that pop up will not be, nor will the solutions that resolve those bugs.

This is also the time to deal with any issues you may have noticed during initialization. For example, earlier in this Guide when I initialized the RTC the date and time were completely wrong.

This will require a lot of experimenting and trial & error. But remember! Since this is a core sensor package, all the work and troubleshooting you do here will help reduce issues you might encounter in future payloads.

Once you reach a point where you are satisfied with the way the code is controlling the sensors, it is time to do some calibrating and testing!\

Next section: Calibrating/Testing
