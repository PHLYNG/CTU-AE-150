# Initialize Sensors

Now we're getting to the exciting stuff!

The first step is to connect each individual sensor to the ESP32 and run sample code to ensure that your sensors are functioning. Please note that for now, we will skip the SD Card Reader in this section. In order to test that device, we will need the sensors working first and then see if the SD Card Reader successfully logs the data that they output.

Also please note that you may need to solder pin headers to your sensors. Head over to the [Soldering](Soldering.md) section for tips and tutorials.

Otherwise, proceed with the following walkthrough to initialize your sensors.

  1. Connect a jumper cable to the 3.3V pin on the ESP32 and then connect the other end to the VCC pin on the sensor
  2. Connect a jumper cable to the GND pin on the ESP32 and then connect the other end to the GND pin on the sensor
     - It is good practice to use red for power and black for ground
  4. Connect a jumper cable to the 22 pin on the ESP32 and then connect the other end to the SCL pin on the sensor
  5. Connect a jumper cable to the 21 pin on the ESP32 and then connect the other end to the SDA pin on the sensor
     - If you look back at the ESP32 diagram in the CDH section, you will see that pins 21 and 22 are labeled SDA and SCL, respectively
  7. When completed, your ESP32 and connected sensor should look like this:
  ![image alt](https://github.com/PHLYNG/HAB-CINT/blob/20d9b02d544302f6e763203ecd196133eb291240/images/PXL_20261029_142621145.jpg)
  8. In the Arduino IDE, select the Library Manager icon

   ![image alt](https://github.com/PHLYNG/CTU-AE-150/blob/1f0a11a02f1457941f0e2fc2d92e6f2c6467ca44/images/Screenshot%202026-10-23%20173251.png)
   
  10. In the search bar that appears, search for the sensor that you have connected to your ESP32
  11. From the results, choose an official library (Adafruit, Sparkfun, Arduino, etc) if available
      - If an official library is not available, feel free to search the internet for which library might be the best for your particular option
      - Otherwise, choosing the first available option should suffice
  ![image alt](https://github.com/PHLYNG/HAB-CINT/blob/20d9b02d544302f6e763203ecd196133eb291240/images/rtc%20lib%20install.png)
  12. When installing a Library package, a popup may appear saying that the Library you're trying to install requires other dependencies that are currently not installed; if that occurs, simply click "INSTALL ALL".
  13. Click File in the top left corner of the Arduino IDE, then hover over Examples from the drop down menu, then select your newly installed Library (which should appear towards the bottom of the window), then select an item from the list. A new window will pop up that is populated with ready to run code.
  14. In this case, I chose the "timestamp" option because I want to see that the RTC can in fact output a timestamp in a readable format and also see what time the RTC thinks it is.
  ![image alt](https://github.com/PHLYNG/HAB-CINT/blob/2d9f36ecec5b79fd75be9da8187411b862420b92/images/rtc%20example%20code%20select.png)
  15. At this point if you haven't already, connect your ESP32 to your computer using a USB-C cable. You should see a red power indicator light activate for both the ESP32 and the RTC.
  16. To upload code to your ESP32 first click the Verify button, which appears as a check mark, in the top left corner of the window. This ensures that the code runs without any errors.
  17. Once that process is complete, next click the Upload button, which is directly to the right of the Verify button and appears as an arrow pointing to the right.
  18. To see the output of the sensor, you must open the Serial Monitor. You can use the keyboard shortcut of CTRL+SHIFT+M, or click on the Tools button at the top left of the window, and then click Serial Monitor from the drop down menu.
  19. You will most likely see random symbols or nothing at all. This is because the Serial Monitor defaults to read at 9600 baud.
  ![image alt](https://github.com/PHLYNG/HAB-CINT/blob/6980f473542e5f265675f468a925955494222235/images/rtc%20serial%20monitor%209600%20baud.png)
  20. Note that in the code, a baud setting is entered. Therefore, the Serial Monitor setting needs to match this value.
  21. Select the baud setting menu and select the value that matches the value in the code. In this case, it's 57600 baud.
  22. After making the switch, sensor output should appear in the Serial Monitor.
  ![image alt](https://github.com/PHLYNG/HAB-CINT/blob/6980f473542e5f265675f468a925955494222235/images/rtc%20serial%20monitor%20correct%20baud.png)

You will need to repeat this process with your remaining sensors. Once you have done so, we start building an integrated circuit and write the code that will control your sensors!
