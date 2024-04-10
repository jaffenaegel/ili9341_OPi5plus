# ili9341_OPi5plus
## Repo for driving the LCD display at around 30FPS on an orange pi 5 plus

As I scoured the internet to find a way to drive the lcd display on the orangepi 5 plus using SPI. I found some repo's but couldn't get them to work on my system (or at least not above 5FPS) so I made my own code based on spidev and wiringPi. This library can be used in python or in c. 

### How to use it
In order to use this you need to connect your device as such that:
* A 5V pin of the OPi5+ is connected to VCC on the display
* A GND pin of the OPi5+ is connected to GND on the display
* Pin 24 (WPi-counting) of the OPi5+ is connected to CS on the display
* Pin 3 (WPi-counting) of the OPi5+ is connected to RESET on the display
* Pin 10 (WPi-counting) of the OPi5+ is connected to DC on the display
* Pin 19 (WPi-counting) of the OPi5+ is connected to SDI<MOSI> on the display
* Pin 23 (WPi-counting) of the OPi5+ is connected to SCK on the display
* Pin 4 (WPi-counting) of the OPi5+ is connected to LED on the display
* Pin 21 (WPi-counting) of the OPi5+ is connected to SDO<MISO> on the display

After that, in C you can compile ili9341.c to a shared dll using the following command
~~~bash
gcc -shared -o ili9341.so ili9341.c -fPIC -lwiringPi
~~~

The ili9341.so file can then be called in python using the ctypes library. I will make a class that has these features pre-installed so you can use it in python.

### Issues
As of now, there are a few optimisations that can be added. If I do not add them soon, feel free to open an issue to remind me :).
* Clearer and more complete explanation to install and use this library, including images of the steps
* State of the art implementation in python
* Add touchscreen support
* Process images and videos, like the HDMI input of the OPi5+
* Implementation of a simple, easy to use widgets that can be added on the screen: Labels, Buttons and Sliders on a FloatLayout
