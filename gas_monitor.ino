/*
Gas Monitor Project
Final version 1
=================

#connections:
ARDUINO | SENSORS&DISPLAY
--------------------------
GND       GND (ALL)
5V        VCC (ALL)
A0        A0  (GAS)
A4        SDA (DISP)
A5        SCL (DISP)
9         OUTPUT (BUZZER)

*/

#include <Wire.h> // needed for use of LCD
#include <LiquidCrystal_I2C.h>  // LCD library

// creating object of the LiquidCrystal_I2C class (instance for our single display)
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// put details here about your info, max. 16 characters per name
char project[] = " GasMonitor_TM ";  // PROJECT NAME 
char team[] = " IUS ";  // TEAM NAME

// PIN DEFINITIONS
#define gasSensor A0
#define buzzer 9

// if the gas value goes abote threshold, the alarm goes off
// max sensor reading is 1023
#define THRESHOLD 500

void setup(){
  lcd.begin(16,2); // Defining the screen size of the display, 16 columns and 2 rows
  lcd.backlight(); // To Power ON the back light of the display

  // Loading screen, when the display is turning ON
  lcd.setCursor(0,0);
  lcd.print(project);  
  lcd.setCursor(0,1);
  lcd.print(team);  
  delay(3000);

  lcd.clear(); // Clear the screen
  lcd.setCursor(0,0); // Defining positon to write to (column, row)
  lcd.print("Gas concenration"); // 16 characters per line MAX

  pinMode(buzzer, OUTPUT); // setting the buzzer pin to OUTPUT mode
  pinMode(gasSensor, INPUT); // setting the gas sensor pin to INPUT mode (not need to write actually, because ANALOG pins are INPUT ONLY)
}

void loop(){
  int gasSensorValue = analogRead(gasSensor); // reading the gas value
  
  // check if the threshold is surpassed
  // if yes => turn on the alarm
  // if not => turn off the alarm
  if(gasSensorValue >= THRESHOLD){
    digitalWrite(buzzer, HIGH);
  }else{
    digitalWrite(buzzer, LOW);
  }
  
  lcd.setCursor(6,1); // Setting to middle of the screen
  lcd.print(gasSensorValue); // Print gas value
  
  delay(1000); // read every 1 second

  // clear the second row only
  lcd.setCursor(6,1);
  lcd.print("    ");
}
