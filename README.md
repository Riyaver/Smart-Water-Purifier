# Smart-Water-Purifier
This IoT enabled water purifier gives “Real time monitoring” to the customer both on an 16x2 LCD display attached to the purifier and their mobile phone through Blynk app.
Components used:
1.	ESP8266
2.	16x2 LCD
3.	TDS sensor
4.	DS18b20 temperature sensor
5.	I2C module of 16x2
6.	AC to DC convertor 
7.	Breadboard
8.	Jumper wires 

Software and platform used:
1.	Arduino IDE
2.	Blynk app

Features: 
1.	Wi-Fi symbol: As soon as the device is connected to Wi-Fi, the Wi-Fi Symbol is displayed on top right of LCD screen and when the device is not connected to Wi-Fi, this symbol starts blinking, indicating its disconnection to Wi-Fi.

2.	TDS: TDS is an essential quality parameter of water, TDS is the total dissolved solids in the water, these dissolved solids are inorganic salts such as calcium, magnesium, bicarbonates. TDS sensor is used to display the quantity. TDS is displayed on both LCD screen (on the first row) and Blynk app.

3.	Temperature: Water temperature is on the LCD screen and Blynk app using DS18b20 temperature sensor. It is displayed on the second row of LCD.

4.	Electrical Conductivity: It tells us about the conductivity of water is an essential parameter in order to calculate TDS, as it measures the inorganic components in water.
EC is also calculated with TDS sensor. EC is displayed on the second row of LCD screen and also on the Blynk app.
 

5.	Toggle button: A toggle button is used on Blynk app, to toggle between temperature and EC values on the second row of LCD.

 
Fig 37: EC and TDS toggle
