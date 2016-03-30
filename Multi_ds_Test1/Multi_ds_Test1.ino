// This Arduino sketch reads DS18B20 "1-Wire" digital
// temperature sensors.
// Tutorial:
// http://www.hacktronics.com/Tutorials/arduino-1-wire-tutorial.html

#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

// Connections:
// rs (LCD pin 4) to Arduino pin 12
// rw (LCD pin 5) to Arduino pin 11
// enable (LCD pin 6) to Arduino pin 10
// LCD pin 15 to Arduino pin 13
// LCD pins d4, d5, d6, d7 to Arduino pins 5, 4, 3, 2
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int backLight = 13; // pin 13 will control the backlight

// Data wire is plugged into pin 8 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Assign the addresses of your 1-Wire temp sensors.
// See the tutorial on how to obtain these addresses:
// http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html

DeviceAddress insideThermometer = { 0x28, 0x52, 0x83, 0xDE, 0x04, 0x00, 0x00, 0x51 };
DeviceAddress outsideThermometer = { 0x28, 0x2E, 0x88, 0x15, 0x05, 0x00, 0x00, 0xC2 };

void setup(void)
{
// Start up the library
sensors.begin();
// set the resolution to 10 bit (good enough?)
sensors.setResolution(insideThermometer, 10);
sensors.setResolution(outsideThermometer, 10);

pinMode(backLight, OUTPUT);
digitalWrite(backLight, HIGH); // turn backlight on. Replace 'HIGH' with 'LOW' to turn it off.
lcd.begin(20,4); // columns, rows. use 16,2 for a 16x2 LCD, etc.
lcd.clear(); // start with a blank screen
}

void printTemperature(DeviceAddress deviceAddress)
{
float tempC = sensors.getTempC(deviceAddress);
if (tempC == -127.00) {
lcd.print("Error");
} else {
lcd.print(tempC);
// lcd.print("/");
// lcd.print(DallasTemperature::toFahrenheit(tempC));
}
}

void loop(void)
{ 
//  lcd.clear();
delay(2000);
sensors.requestTemperatures();
lcd.setCursor(0,0);
lcd.print("SensorA: ");
printTemperature(insideThermometer);
// print the number of seconds since reset:
// lcd.setCursor(0,1);
//  lcd.print(millis()/1000);
lcd.setCursor(0,2);
lcd.print("SensorB: ");
printTemperature(outsideThermometer);
  lcd.setCursor(0,3);
  lcd.print("Last Reset=");
  lcd.setCursor(11,3);
  lcd.print(millis()/1000);
  
}
