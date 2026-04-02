This is another internal file.

This journal is meant to document anything related to my SD that could be useful somehow.

4/2/26
- learned from Dan that the BMP085's altitude limit isn't high enough for a 100,000ft flight
- verified that and found that it's limit is about 30,000ft
- the correct pressure sensor to use is the [MS5611](https://www.amazon.com/MS5611-01BA03-Precision-Atmospheric-Pressure-arduino/dp/B0DRBP4C2W?crid=O7EVO50W6BZ4&dib=eyJ2IjoiMSJ9.p8sGZe8ZF3H6jYkP3uDNiAB3InW1uAs6KipKdNN-pzkKvhRRAbgPeanAKgsTRrUqNN39JmbuD8R4x8D94Af9tjOGT_lzO1nD-P2Df-NDQtA-joT3RlSH5S1OtoBarvIhFv-RTVxKQsk8mgMUGYiaDhX67ofbeB9KK1IwIvZRo0W3qeuDZ0iY9Mo7ha0HjQPuEURlZqHgOlC7vmwJ5ta-N-QjxQhsE6mGN0iNlJeB2sI.oap_TaDN3J67NxGxiX8cBKnZ63B8ylirwRSBfUN7EsM&dib_tag=se&keywords=ms5611&qid=1775155155&sprefix=ms5611%2Caps%2C169&sr=8-3)
- for remote sensing, I think i'm just gonna let it ride and see what happens
- 5 sensors is too many to breadboard (physical space limitation)

3/27/26
  - Capturing data every 2 seconds with BMP085 and BNO055 for about 5 minutes = 4.91kb of data
    - 4.91 * 12 = 58.92 kb per hour
    - 58.92 * 4 = 235.68 kb for a 4 hour flight
  - Capturing data every 10 times per second with BMP085 and BNO055 for about 5 minutes = 81.6kb of data
    - 4.91 * 12 = 979.2 kb per hour
    - 58.92 * 4 = 3916.8 kb for a 4 hour flight
  - 1 Mb per hour of data for 2 sensors
  - even if that number doubles because we have two more sensors, data storage will not be a problem
  - caution! the previous file will be overwritten as the code currently stands
  - should i include a hard data logging stop? maybe after 5 hours?
  - WHAT'S NEXT? WHAT'S LEFT?
    - still need to add 3 more sensors to this prototype (one more temp, shock, and humidity)
    - from there, can finalize code
    - once code is locked in, need to determine physical design where one of the temp sensors is on the outside of the payload
    - assemble
    - fly?!

3/26/26
  - experimenting with the esp32
  - found a number of things that students will need for troubleshooting purposes
  - https://www.youtube.com/watch?v=ZoIgoHZiXFI
  - this video will help you determine if the device is being recognized at all
  - if it's not, you will need to install drivers
  - https://www.silabs.com/software-and-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads
  - the readme has instructions for installing the driver, it's very painless

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
