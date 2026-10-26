# Command & Data Handling (CDH)

A microcontroller unit (MCU) functions as a compact, self-contained computer fabricated on a single integrated circuit. Designed to control targeted operations within an embedded system without the overhead of a general-purpose operating system, a MCU directly governs sensor software integration, power distribution, and payload data logging.

This Manual uses an ESP32 rather than an Arduino as the MCU of choice for CDH functions. The ESP32 is a more powerful device that costs only slightly more (if not about the same) as an Arduino unit. At the same time, the user can program an ESP32 with an Arduino IDE using the same Arduino libraries for the sensor package.

  ![image alt](https://github.com/PHLYNG/CTU-AE-150/blob/3c44d6c381834538819a3806c4304dc34bd8db5d/images/esp32%20pinout.jpg)

To setup the ESP32, follow the instructions below:

1. [Download Arduino IDE](https://www.arduino.cc/en/software/), go through installation process
2. [Download driver](https://www.silabs.com/software-and-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads)
  1. Windows - download CP210x Universal Windows Driver
  2. MacOS - download CP210x VCP Mac OSX Driver
3. Extract driver file
4. In the extracted driver file, right click the file titled “silabser” and select install
    1. The file may have an extension “.inf” or you might see a column in your file manager where         the file type is “setup information”
    2. If you have further trouble, the driver file will have a text file with detailed                   instructions
5. In Arduino IDE, at the top left select “Tools,” then select “Boards,” then select “Boards Manager”

   ![image alt](https://github.com/PHLYNG/CTU-AE-150/blob/6acf5c7a29f375a35f7b22e94a33aef4772e322f/images/Screenshot%202026-10-08%20163729.png)
7. In the top left of the newly opened window, click into the search bar and search "ESP32"

   ![image alt](https://github.com/PHLYNG/CTU-AE-150/blob/77fea9497a12ade1bd98f81b4cc51e11e86cf043/images/Screenshot%202026-10-08%20163759.png)
9. Install both libraries by Arduino and Espressif Systems
    1. This installation process will take a few minutes
10. At this point, make sure your ESP32 is plugged in to your computer
11. In the main Arduino IDE window, select the "Select Board" box
    ![image alt](
13. In the search bar, search for and select "ESP32 DOIT DevKit" (the correct COM port should automatically be selected)

    ![image alt](https://github.com/PHLYNG/CTU-AE-150/blob/b00f86b29cd741b76f62bf935e3a95e97742a8c6/images/esp32%20adruino%20ide%20selection.png)

You are now ready to upload code to your ESP32! To run some test code on your sensors to make sure they work, go to the Sensor Package section.
