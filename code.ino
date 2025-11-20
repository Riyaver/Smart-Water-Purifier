Code.txt
#define BLYNK_TEMPLATE_ID "TMPL3wPhWoSMv"
#define BLYNK_TEMPLATE_NAME "Water monitoring"
#define BLYNK_AUTH_TOKEN "O_mMRxC6PttpsiDoBGtjg15NRflUTna9"

#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>

#include <WiFiClient.h>

#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <hd44780.h> 
#include <hd44780ioClass/hd44780_I2Cexp.h>

hd44780_I2Cexp lcd;
byte wifi_ok[8] = { 
    0b00000, 
    0b01110, 
    0b10001,
    0b00000, 
    0b00100, 
    0b01010, 
    0b00000, 
    0b00100
};

char ssid[] = "XXXXXX";
char pass[] = "xxxxxx";
char auth[] = BLYNK_AUTH_TOKEN;

namespace pin {
  const byte tds_sensor = A0; //TDS
  const byte one_wire_bus = D6; //Temperature 
}

namespace device {
  float aref = 3.3; 
}

namespace sensor {
  float ec = 0;
  unsigned int tds = 0;
  float waterTemp = 0;
  float ecCalibration = 1;
  bool displayTemperature = true; // Variable to toggle between displaying temperature and TDS on LCD
}

OneWire oneWire(pin::one_wire_bus);
DallasTemperature dallasTemperature(&oneWire);

BLYNK_CONNECTED() {
  Blynk.syncVirtual(V5);
}

BLYNK_WRITE(V5) {
  int pinValue = param.asInt();
  
  if (pinValue == 1) {
    sensor::displayTemperature = true;
  } else {
    sensor::displayTemperature = false;
  }

  Serial.print("V5 button value is: ");
  Serial.println(pinValue);
}

void setup() {
  Serial.begin(115200); 
  Blynk.begin(auth, ssid, pass);
  dallasTemperature.begin();
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, wifi_ok);
}

void loop() {
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    lcd.setCursor(15, 0); 
    lcd.write(0);
    delay(1000);
    lcd.clear();
  }
  
  delay(1000);
  lcd.setCursor(15, 0); 
  lcd.write(0);
  Blynk.run();
  readTdsQuick();
  delay(1000);
}

void readTdsQuick() {
  dallasTemperature.requestTemperatures();
  sensor::waterTemp = dallasTemperature.getTempCByIndex(0);
  float rawEc = analogRead(pin::tds_sensor) * device::aref / 1024.0;
  float temperatureCoefficient = 1.0 + 0.02 * (sensor::waterTemp - 25.0);
  sensor::ec = (rawEc / temperatureCoefficient) * sensor::ecCalibration;
  sensor::tds = (133.42 * pow(sensor::ec, 3) - 255.86 * sensor::ec * sensor::ec + 857.39 * sensor::ec) * 0.5;

  Serial.print(F("TDS:"));  
  Serial.println(sensor::tds);
  Serial.print(F("EC:")); 
  Serial.println(sensor::ec, 2);
  Serial.print(F("Temperature:")); 
  Serial.println(sensor::waterTemp, 2);
  
  Blynk.virtualWrite(V1, (sensor::tds));
  Blynk.virtualWrite(V4, (sensor::ec));
  Blynk.virtualWrite(V3, (sensor::waterTemp));

  updateLCD();
}

void updateLCD() {
  lcd.setCursor(1,0);
  lcd.print(F("TDS:"));
  lcd.print(sensor::tds);
    
  
  
  if (sensor::displayTemperature) {
     lcd.setCursor(1, 1);   
    lcd.print(F("Temp:"));
    lcd.print(sensor::waterTemp, 2);
  } else {
        lcd.setCursor(8, 1);
    lcd.print("   ");
        lcd.setCursor(1, 1);
    lcd.print(F("EC:"));
    lcd.print(sensor::ec);
  }
}
