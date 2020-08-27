# ESPAXA
This module will connect the AXA Remote 2.0 with your Home Assistant Server using ESPHOME. The module will integrate in Home Assistant, showing the position of your Window (open or closed), and give you the possibility to open and close the window from there. The remote control will still work, the status of the window will synchronize with home assistant.

## Power
The module is using a 5V power supply, and I use a DC-DC step-up converter (MT3608) to create the 8V (7.5 with some cable loss) for the AXA Remote from the 5V power supply. So NO batteries needed in your AXA Remote! The Power Supply should have enough capacity to handle the motors inside the AXA. Preferable is a Raspberry Pi supply (model 3, 2.5A or more). The power can be connected via the WEMOS USB plug, or directly to the 5V and GND pin of the WEMOS. The DC-DC Converter should be adjusted to 8V, using a multimeter. You can plug in the power adapter to this module as well for delivering power.
## Schema
This is more like 'connecting the modules'. The DC-DC converter is connected to 5V and the power input of the AXA Remote (pins 1 and 2). The MCP2003 is the LINBUS driver. It has some special 'low power'capabilities we will not use. Therefor the /WAKE function is disabled, and Vren is not used. RxD is the OUTPUT signal! It should be connected to Rx of the Wemos. This is a 'open drain' output, so we have to pull-up to 3.3V to create a Wemos compatible signal. The input is Tx, this is a TTL compatible input, but will accept the 3.3V as a '1'. The decoupling capacitors used are 47uF, but any value > 10uF is OK. As an extra a BMP/BME280 module is integrated to measure Temperature, Pressure and Humidity (BME). A nice feature of ESPHOME, just to show, but not neccesary for the AXA control.
![Schema](https://raw.githubusercontent.com/galagaking/espaxa/master/docs/Schematic_ESP_AXA_2020-08-26_21-20-54.png)
## Components
Sometimes difficult to find, my sources (NO affiliate links :-) ):
- [Step-up converter MT3608](https://www.tinytronics.nl/shop/nl/spanning-converters/step-up/dc-dc-verstelbare-step-up-boost-converter-mt3608-2a)
- [MCP2003](http://www.okaphone.com/artikel.asp?id=485422)
- [Wemos D1 Mini v3](https://www.tinytronics.nl/shop/nl/communicatie/wi-fi/wemos-d1-mini-v2-esp8266-12f-ch340)
- [RJ12 cable](https://www.tinytronics.nl/shop/nl/kabels/adapters/rj12-naar-6-pins-dupont-jumper-adapter)
- [BME280 sensor](https://www.tinytronics.nl/shop/nl/sensoren/temperatuur-lucht-vochtigheid/bme280-digitale-barometer-druk-en-vochtigheid-sensor-module)
- [Power Supply](https://www.tinytronics.nl/shop/nl/raspberry-pi/voedingen/raspberry-pi-micro-usb-voeding-5.1v-2.5a-zwart-t6716dv)

## Reference
- [Data sheet MCP 2003](http://ww1.microchip.com/downloads/en/devicedoc/22230a.pdf)
- [AXA Documentation](http://files.domoticaforum.eu/uploads/Axa/AXA%20Remote%202%20domotica%20English%202012nov_V2.pdf)

## Construction
No PCB (yet), so you have to use a protoboard to connect the components. Before connecting the AXA and the MCP (if you use a socket), measure the voltage on the MCP2003 pins (8V) and the AXA connector.
![ESPAXA](https://raw.githubusercontent.com/galagaking/espaxa/master/docs/espaxa.png)
## Programming
We use ESPHOME to create the program file. This is more like a configuration than a program. espaxa.yaml has all the definitions, and is also referring to some program code in AXA\espaxa.h. You have to create this directory and put the expaxa.h file in it. Also fill in the WiFi credentials (or better: use the secrets file). More info on esphome
[here](https://esphome.io/) or [here](https://www.galagaking.org/2019/11/05/esphome-workshop/). To start, connect the ESPAXA (without connecting the AXA Remote) directly to your USB port to upload the sketch the first time. Now OTA is installed, you can upload any new sketch 'Over the Air'. ESPHOME will try to find the module itself. If not, you have to manage your DHCP server and 'hardcode' an IP address.
## Logs
By looking at the logs (you can use the webserver at the modules address, the serial port output or the esphome logs command), you can see if the module is working. It will output the WiFi connection, Home Assistant connection and at a 30 sec interval the state of your Window. If any command is given, this will show up as well.

[20:44:04][D][sensor:092]: 'Axa Window': Sending state 0.00000  with 0 decimals of accuracy <BR>
[20:44:34][D][espaxa:054]: 211, 211 Strong Locked <BR>
[20:44:34][D][sensor:092]: 'Axa Window': Sending state 0.00000  with 0 decimals of accuracy <BR>
[20:44:59][D][cover:072]: 'Zolderraam' - Setting <BR>
[20:44:59][D][cover:082]:   Command: OPEN <BR>
[20:44:59][D][cover:152]: 'Zolderraam' - Publishing: <BR>
[20:44:59][D][cover:160]:   State: CLOSED <BR>
[20:44:59][D][cover:168]:   Current Operation: IDLE <BR>
[20:45:04][D][espaxa:054]: 210, 210 UnLocked <BR>

## Home Assistant
The ESP module will show up as a new integration. After enabling this integration, you can add the entities given in your espaxa yaml file in your interface. The objects will already use their default MDI picture.
![Home Assitant](https://raw.githubusercontent.com/galagaking/espaxa/master/docs/2020-08-25_22-39-03.png)

## Thank you
For inspiration and examples:
- [SuperHouse Automation](https://github.com/SuperHouse/)
- [nldroid CustomP1UartComponent](https://github.com/nldroid/CustomP1UartComponent)

## disclaimer
Use this project as-is, i am not responsible for any unexpected open window at your home, or any damage to any hardware. This is a creative commons project, for non-commercial use only.

## todo

- PCB?


