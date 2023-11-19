/*
This is the Distance & Humidity & Temperature program. aka DHT program.

Goal: This program displays on an LCD screen: the temperature and humidity levels of your room combined with an ultrasonic sensor that can detect nearby objects and display their distance.

Main Theme: Digital Input (digitalRead) + Digital Output (digitalWrite) + pulseIn command.
*/

// Here we include the Library of the LCD.
#include <LiquidCrystal.h>
// Here we include the Library of the DHT11.
#include "DHT.h"

// Here we declared a constant/hardcoded variable called "trigger" and gave it the value of 13 (pin 13 on Arduino).
#define trigger 13
// Here we declared a constant/hardcoded variable called "echo" and gave it the value of 9 (pin 9 on Arduino).
#define echo 9
// Here we declare a constant/hardcoded variable called "DHTPIN" and gave it the value of 7 (pin 7 on Arduino).
#define DHTPIN 7
// Here we declare a constant/hardcoded variable called "DHTTYPE" and gave it the value of DHT11 which was already defined within the DHT library.
#define DHTTYPE DHT11

// Here we define each connection pins of the LCD to its corresponding Arduino pin. 
// We use the constant data type because it's "hardcoded" since we won't change the values of the variables once we declared them.
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
// When we reference our "LiquidCrystal" variable, it comes in a package with all of the Arduino pins that we assigned to variables.
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// When we reference our "DHT" variable, it comes in a package with the pin on Arduino and the type of DHT that we are using.
DHT dht(DHTPIN, DHTTYPE);

// Here we declared two float variable named "duration" and "distance".
float Duration, Distance;
// Here we declared a variable called "PB" and gave it the value of 8 (pin 8 on Arduino).
// This push button is used to switch between "modes" on the LCD (switch between displaying readings of ultrasonic and readings of DHT11).
int PB = 8;

void setup() 
{ 
  // This line enables printing on the LCD screen.
  lcd.begin(16, 2);
  // Here we tell the Arduino that pin 13 (trigger) works as an output.
  pinMode(trigger, OUTPUT);
  // Here we tell the Arduino that pin 9 (echo) works as an input.
  pinMode(echo, INPUT);
  // Here we tell the Arduino that pin 8 (PB) works as an input.
  pinMode(PB, INPUT);
}

void loop() 
{
  // Here we declared an integer variable named "BPval" and gave it the value of the Digital Output of pin 8 of Arduino which is our push button.
  int PBval = digitalRead(PB);
  // Here we declared a float variable named "Temperature" and gave it the value of wathever the DHT11 sensor reads for temperature.
  float Temperature = dht.readTemperature();
  // Here we declared a float variable named "Humidity" and gave it the value of wathever the DHT11 sensor reads for humidity. 
  float Humidity = dht.readHumidity();

  // This line tells the Arduino to send 0V digital output to pin 13.
  digitalWrite(trigger, LOW);
  // This pauses the program for 2 microseconds.
  delayMicroseconds(2);
  // This line tells the Arduino to send 5V digital output to pin 13.
  digitalWrite(trigger, HIGH);
  // This pauses the program for 10 microseconds.
  delayMicroseconds(10);
  // This line tells the Arduino to send 0V digital output to pin 13.
  digitalWrite(trigger, LOW);

  // Here we gave our duration variable the value of the pulse we read on pin 9 (echo).
  Duration = pulseIn(echo, HIGH);

  // Here we gave our distance variable the values of half the duration multiplied by 0.0343
  // This equation allows us to find the distance between the tip of the ultrasonic sensor and the body of the object we are detecting.
  Distance = (Duration/2) * 0.0343;

  // IF our PBval is equal to 0 (PB not pressed)...
  if (PBval == 0)
{
  // set the "cursor" to the top line on the LCD screen (first row)
  lcd.setCursor(0, 0);
  // print the word: "Distance = " on the LCD.
  lcd.print("Distance = ");
  // and IF our distance is bigger or equal to 400 & smaller or equal to 2...
  if (Distance >=  400 || Distance <= 2)
  {
    // Here we "set" the "cursor" to the line below on the LCD screen (second row)
    lcd.setCursor(0, 1);
    // print the words: "Out of range" on the LCD.
    lcd.print("Out of range");
  }
  //IF NOT...
  else
  {
    // Clear the LCD screen of any writting.
    lcd.clear();
    // set the "cursor" to the top line on the LCD screen (first row)
    lcd.setCursor(0, 0);
    // print the word: "Distance = " on the LCD.
    lcd.print("Distance = ");
    // set" the "cursor" to the line below on the LCD screen (second row)
    lcd.setCursor(0, 1);
    // print the distance value stored within our Distance variable on the LCD.
    lcd.print(Distance);
    // print the unit: " cm" on the LCD.
    lcd.print(" cm");
    // freeze the program for half a second.
    delay(500);
  }
}
// ELSE IF the PBval is equal to 1 (PB is pressed)...
else if(PBval == 1)
  {
    // Clear the LCD screen of any writting.
    lcd.clear();
    // set the "cursor" to the top line on the LCD screen (first row)
    lcd.setCursor(0, 0);
    // print the word: "Temperature = " on the LCD.
    lcd.print("Temperature = ");
    // set" the "cursor" to the line below on the LCD screen (second row)
    lcd.setCursor(0, 1);
    // print the temperature value stored within our Temperature variable on the LCD.
    lcd.print(Temperature);
    // freeze the program for half a second.
    delay(500);
  }
}
