/*
This is the LCD Ohmmeter program.

Goal: This program simulates an ohmmeter that reads the resistance value of any resistor of choice. And displays the readings on an LCD.
(requires two resistors: one of 1k ohm and another of value of choice) (1k ohm resistor is used to calculate the current)

Main Theme: Analog Input + Custom characters using lcd.Write and bytes.
*/

// Here we include the Library of the LCD.
#include <LiquidCrystal.h>
// Here we define each connection pins of the LCD to its corresponding Arduino pin. 
// We use the constant data type because it's "hardcoded" since we won't change the values of the variables once we declared them.
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
// When we reference our "LiquidCrystal" variable, it comes in a package with all of the Arduino pins that we assigned to variables.
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Here we have a special character made using binary code.
// This one is half of the Omega symbol we use to indicate the "ohm" unit.
byte omegaA[8] = 
{
	0b00011,
	0b00100,
	0b01000,
	0b01000,
	0b01000,
	0b00100,
	0b10010,
	0b11110
};

// This is the other half of the symbol.
byte omegaB[8] =
{	
	0b11000,
	0b00100,
	0b00010,
	0b00010,
	0b00010,
	0b00100,
	0b01001,
	0b01111
};

// Here we declared a variable called "PB" and gave it the value of 13 (pin 13 on Arduino).
// This is for a push button we use as a "start" button for our ohmmeter.
int PB = 13;

void setup()
{
  // Here we tell the Arduino that pin 13 (PB) works as an input.
  pinMode(PB, INPUT);
  // This line enables printing on the LCD screen.
  lcd.begin(16, 2);
  // Here we print the word: "Ohm meter" on the LCD.
  lcd.print("Ohm meter:");
  // This code is used to create our custom character.
  // Indicating "omegaA" as 0.
  lcd.createChar(0, omegaA);
  // Indicating "omegaB" as 1.
  lcd.createChar(1, omegaB);
}

void loop() 
{
// Here we declared an integer variable named "BPval" and gave it the value of the Digital Output of pin 13 of Arduino which is our push button.
int PBval = digitalRead(PB);
// Here we "set" the "cursor" to the line below on the LCD screen (second row)
lcd.setCursor(0,1);
// Here we declared a float variable named "Bit" and gave it the value of the Analog Input pin zero of the Arduino.
// So whatever value the Arduino reads, it will be stored inside the "Bit" variable.
float Bit = analogRead(A0);
// Here we declared another float variable called "Voltage" and gave it the value of our "Bit" variable multiplied by 0.005.
// This equation turns the bit value of analogRead into voltage values.
float Voltage = Bit * (5.0/1023.0);
// Here we declared another float variable called "Vacross" and gave it the value of 5 (5V of Arduino) minus our voltage value to find the voltage across.
float Vacross = (5 - Voltage);
// Here we declared another float variable called "Current" and gave it the value of our voltage across divided by 1000 (1k ohm resistor).
float Current = Vacross/1000;
// Here we declared another float variable called "Resistance" and gave it the value of our voltage divided by our current (ohm's law).
float Resistance = Voltage/Current;
// Here we print the word: "R = " on the LCD.
lcd.print("R = ");
// This line tells the Arduino that IF the value stored within our "PBval" variable is equal to 0...
if(PBval == 0)
{
  // print the word: "OL       " on the LCD.
  lcd.print("OL         ");
}
// IF not...
else
{
  // print the resistance value stored within our Resistance variable on the LCD.
  lcd.print(Resistance);
  // And also print the custom characters.
  lcd.write(byte(0));
  lcd.write(byte(1));
}
}
