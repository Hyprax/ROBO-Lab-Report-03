/*
This is the LCD Voltmeter program.

Goal: This program simulates a voltmeter using a potentiometer to adjust the voltage which is displayed on the LCD screen.

Main Theme: Analog Input + lcd.print command.
*/

// Here we include the Library of the LCD.
#include <LiquidCrystal.h>
// Here we define each connection pins of the LCD to its corresponding Arduino pin. 
// We use the constant data type because it's "hardcoded" since we won't change the values of the variables once we declared them.
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
// When we reference our "LiquidCrystal" variable, it comes in a package with all of the Arduino pins that we assigned to variables.
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() 
{
  // This line enables printing on the LCD screen.
  lcd.begin(16, 2);
  // Here we print the word: "Voltmeter" on the LCD.
  lcd.print("Voltmeter:");
}

void loop() 
{
// Here we "set" the "cursor" to the line below on the LCD screen (second row)
lcd.setCursor(0,1);
// Here we declared a float variable named "Bit" and gave it the value of the Analog Input pin zero of the Arduino.
// So whatever value the Arduino reads, it will be stored inside the "Bit" variable.
float Bit = analogRead(A0);
// Here we declared another float variable called "Voltage" and gave it the value of our "Bit" variable multiplied by 0.005.
// This equation turns the bit value of analogRead into voltage values.
float Voltage = Bit * (5.0/1023.0);
// Here we print the word: "Voltage = "on the LCD
lcd.print("Voltage = ");
// Here we print the voltage value stored within the Voltage variable.
lcd.print(Voltage);
}

