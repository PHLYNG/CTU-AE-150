# Integration

Once each sensor is powered on and confirmed to be functioning properly, connect everything together into a single circuit.

## Prototyping - Initial Assembly on Solderless Breadboards

Before assembling a permanent soldered board or perfboard, all components should first be wired using solderless breadboards.

Two major advantages of using breadboards:

  1. A breadboard allows components, power distribution lines, and signal jumpers to be rearranged dynamically without desoldering or damaging delicate board pads.
  2. Prototyping on a breadboard makes early wiring errors, such as landing a jumper cable on the wrong pin or misrouting a digital bus line, completely reversible and low stakes. Mistakes can be caught and corrected immediately during pre-assembly bench testing before any permanent soldering takes place.

Here is a diagram of how a breadboard works:

![image alt](https://github.com/PHLYNG/HAB-CINT/blob/cbf6dc40e3856e4c5aac83eab86c16e7c659f563/images/breadboard-illustrated.adb3be7b.jpg)

Note that all three sensors in the sensor package have the same VCC, GND, SDA, and SCL pins.

## SD Card Reader

Now we can finally introduce the SD Card Reader into the circuit. This component needs to be connected to the 5V pin on the ESP32 because it has current requirements that are greater than the sensors. If these requirements aren't met the SD Card Reader may not spin up when the payload is powered on, or it may drop in and out resulting in inconsistent data logging if not a total loss in data logging.

The end result should look something like this:

![image alt](https://github.com/PHLYNG/HAB-CINT/blob/8a8657c83d32f21084fcae816d20b478ab925065/images/PXL_20261029_184732134.jpg)

Note that tidiness is critical! Having jumper cables of different lengths and colors helps with this. Establishing conventions, even if only for yourself, for what colors go with what pins is also helpful for keeping track of things and debugging if you run into any issues.

## Code

One of the few things this Guide will not fully walk through is how to write the code for your integrated circuit.

This is an area where one size will not fit all. Each individual user may want to see their data logged in a different way, or give more weight to certain data types over others. Even though the sensor package is the same, the bugs that pop up will not be, nor will the solutions that resolve those bugs.

## Finalizing Layout
