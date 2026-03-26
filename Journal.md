This is another internal file.

This journal is meant to document anything related to my SD that could be useful somehow.

3/25/26
  - starting to mess with ESP32 board

3/23/26
  - did a presentation dry run with Volosin
  - got some great feedback
  - refined what my 3 payloads will be
    - measure payload operating environment with little environmental control (ie insulation)
    - alter payload environment, like with insulation
    - tweak, finalize, verify chosen parameters
  - launch one payload during summer (aiming for right after semester ends)
  - Volosin thinks it's ok to launch remaining two at the start of fall semester (ie don't feel like i need to rush launches over the summer)
  - i will aim to launch two over the summer and launch third at the start of fall semester
  - struggled a lot with SD card reader, according to Dan arduino struggles due to small amounts of memory
  - got Dan's AE150 kicad files and things

3/22/26
  - what are my test payloads going to be?
    - something basic
    - shock
    - RF

3/20/26
  - i'm able to fire up each component individually and see data in the IDE console
  - now trying to hook up 4 different components to a single arduino
     - BMP085
     - BNO055
     - DS3231 Real Time Clock
     - SD Card Adapter
  -  ~i tried funneling each component via breadboard into a single A4 port (for example), but doesn't work~
  -  ~i think the thing to do is to configure different ports to act like A4 and A5~
  -  i did not lay the connectors out properly on the breadboard before, now i have
  -  i have now successfully initialized each component (not counting the sd card adapter) on the breadboard without having to change the wiring between setups
  - next challenge is to figure out how to write data to the sd card
     - start by writing data from one sensor, then add the next, then the next
     - need to determine what the best format is for data logging
     - ideally the students take the data and plot it on their own using matlab
  - questions
     - some sensors have different default baud rates - can these all be set to the same baud rate?
     - initial read is that each sensor can be set to the same baud rate

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

3/12/26
  - soldered BMP388
  - but I soldered the wrong directions (long pins need to be able to plug into a breadboard)

3/5/26 
  - began organizing electronics components in the FL in the bin rack to to better understand what we have on hand

3/2/26 
  - talked with Dan about the HAB tracking device (what's it called?) and confirmed that it is GPS only
  - the goal is still to transmit data during flight, so this by itself won't solve that issue
  - might still want to have a GPS option onboard to ensure recovery (or at least increase the chances of recovery)

2/16/26 
  - ordered x3 ESP32 microprocessors and x2 BMP388 temperature/pressure/altitude sensors
