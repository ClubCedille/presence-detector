# presence-detector

## Dev Environment Setup

### Hardware

- Wireless Module NodeMcu 

  [sample provider link](https://www.amazon.ca/Wireless-NodeMcu-Nodemcu-Development-Products/dp/B07JLPGCT8/ref=sr_1_fkmr0_3?ie=UTF8&keywords=Lua%20Nodemcu%20WIFI%20Network%20Development%20Board%20Based%20ESP8266%20HIGH%20QUALITY&language=en_CA&qid=1547681099&sr=8-3-fkmr0)

- BreadBoard
- Light dependent resistor
- USB to mini-usb wire


###  Software

Using [Arduino IDE](https://www.arduino.cc/en/Main/Software): 

1. Download and install.
2. Start Arduino IDE and go in __File > Preferences__ or hit __Ctrl__ + __,__.
3. In the _Additional Boards Manager URLs_ text box, add the url below:

http://arduino.esp8266.com/stable/package_esp8266com_index.json

4. Click OK. The settings window will close.
5. Under __Tools > Board > Boards Manager...__, install the _esp8266 by ESP8266 Community_ package.  
6. Under the __Tools__ section, set the following properties:
  
Board : "NodeMCU 1.0(ESP-12E Module)"

Upload Speed : "11200"

CpuFrequency : "80 MHz"

Debug Port : Serial


__Linux__

Port : /dev/ttyUSB0

7. To use the monitor, hit __Ctrl__ + __Shift__ + __M__ and set it to 9600 baud.
