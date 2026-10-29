# Integration

Once each sensor is powered on and confirmed to be functioning properly, connect everything together into a single circuit.

## Prototyping - Initial Assembly on Solderless Breadboards

Before assembling a permanent soldered board or perfboard, all components should first be wired using solderless breadboards.

Two major advantages of using breadboards:

  1. A breadboard allows components, power distribution lines, and signal jumpers to be rearranged dynamically without desoldering or damaging delicate board pads.
  2. Prototyping on a breadboard makes early wiring errors, such as landing a jumper cable on the wrong pin or misrouting a digital bus line, completely reversible and low stakes. Mistakes can be caught and corrected immediately during pre-assembly bench testing before any permanent soldering takes place.

Note that all three sensors in the sensor package have the same VCC, GND, SDA, and SCL pins.

The end result should look something like this:

![image alt](https://github.com/PHLYNG/HAB-CINT/blob/8a8657c83d32f21084fcae816d20b478ab925065/images/PXL_20261029_184732134.jpg)

Note that tidiness is critical! Having jumper cables of different lengths and colors helps with this. Establishing conventions, even if only for yourself, for what colors go with what pins is also helpful for keeping track of things and debugging if you run into any issues.

## Code

## Finalizing Layout
