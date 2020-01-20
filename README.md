# Esp-turtle-remote-control

We control the robot in Minecraft using ESP Wemos D1

This project will allow you to control a turttle robot from a computercraft mod from your Wemos D1 or Node MCU connected to the Lcd Keypad Shield

To control the Lcd Keypad Shield, I use [THIS LIB](https://github.com/kolandor/LCD-Keypad-Shield-Wemos-D1-Arduino-UNO)
And [THIS LIB](https://github.com/kolandor/Computercraft-Easy-Turtle-API) to easy turtle robot control

**EASY SETUP**
- Connect LCD Keypad Shield to board with ESP8266 on board (Wemos D1 R1, Node MCU...)
- Flash it
- Put code from **Minecraft-computercraft-turtle** to turtle robot in minecraft
- Change the IP in the [webControl file](Minecraft-computercraft-turtle/webControl.lua) Minecraft-computercraft-turtle/webControl.lua to the IP shown on the LCD keeypad Shield
- Run **webControl**
