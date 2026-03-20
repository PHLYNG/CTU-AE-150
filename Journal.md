This is another internal file.

This journal is meant to document anything related to my SD that could be useful somehow.

2/16/26 
  - ordered x3 ESP32 microprocessors and x2 BMP388 temperature/pressure/altitude sensors

3/2/26 
  - talked with Dan about the HAB tracking device (what's it called?) and confirmed that it is GPS only
  - the goal is still to transmit data during flight, so this by itself won't solve that issue
  - might still want to have a GPS option onboard to ensure recovery (or at least increase the chances of recovery)

3/5/26 
  - began organizing electronics components in the FL in the bin rack to to better understand what we have on hand

3/12/26
  - soldered BMP388
  - but I soldered the wrong directions (long pins need to be able to plug into a breadboard)

3/16/26
  - soldered BMP388 the right way
  - installed Adafruit libraries on my Arduino IDE
  - wired everything up, but how do i record data?
     - use the serial monitor in arduino ide to see output
     - need to make sure that baud rate is set to correct level (the number in serial monitor matches what is written in code)
     - the demo code had baud rate set as 115200. why was this number selected?
  - used the example code from the library
  - sensor appears to be accurate, at least with temperature
  - need to see how i can refine the pressure measurement because the variable is set to sea-level pressure (1013.25 hpa)
  - used arduino uno, connected SDI to A5 and SCK to A4
  - I2C versus serial
     - can hook up more sensors using I2C
<img width="857" height="451" alt="image" src="https://github.com/user-attachments/assets/af209248-20de-4f6c-82e3-432adc92e1a6" />

3/20/26
  -  now trying to hook up 4 different components to a single arduino
    - BMP085
    - BNO055
    - DS3231 Real Time Clock
    - SD Card Adapter
