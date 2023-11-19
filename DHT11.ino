/*
This is the DHT11 program with the LCD.

Goal: This program allows us to use a temperature and humidity sensor and display those readings onto an LCD screen.

Main Theme: dht.read command + lcd.print 
*/

// Here we include the Library of the DHT11.
#include "DHT.h"
// Here we include the Library of the LCD.
#include <LiquidCrystal.h>
// Here we define each connection pins of the LCD to its corresponding Arduino pin. 
// We use the constant data type because it's "hardcoded" since we won't change the values of the variables once we declared them.
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
// When we reference our "LiquidCrystal" variable, it comes in a package with all of the Arduino pins that we assigned to variables.
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// Here we declare a constant/hardcoded variable called "DHTPIN" and gave it the value of 7 (pin 7 on Arduino). 
#define DHTPIN 7
// Here we declare a constant/hardcoded variable called "DHTTYPE" and gave it the value of DHT11 which was already defined within the DHT library.
#define DHTTYPE DHT11
// When we reference our "DHT" variable, it comes in a package with the pin on Arduino and the type of DHT that we are using.
DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
// This line enables printing on the LCD screen.
lcd.begin(16, 2);
// This enables the DHT11.
dht.begin();
}

void loop() 
{
// This line pauses the program for 2 seconds.
delay(2000);
// Here we declared a float variable named "Humidity" and gave it the value of wathever the DHT11 sensor reads for humidity. 
float Humidity = dht.readHumidity();
// Here we declared another float variable named "Temperature" and gave it the value of wathever the DHT11 sensor reads for temperature.
float Temperature = dht.readTemperature();
// Here we print the word: "Humidity: " on the LCD.
lcd.print("Humidty: ");
// Here we print the humidity value stored within the Humidity variable.
lcd.print(Humidity);
// Here we print the percentage symbol next to the numerical values of the humidity.
lcd.print("%");
// Here we "set" the "cursor" to the line below on the LCD screen (second row)
lcd.setCursor(0,1);
// Here we print the word: "Temperature: " on the LCD.
lcd.print("Temperature: ");
// Here we print the temperature value stored within the Temperature variable.
lcd.print(Temperature);
// Here we print the degree symbol next to the numerical values of the temperature.
lcd.print("°C");
}
