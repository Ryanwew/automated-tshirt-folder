#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Bounce2.h> // Include the Bounce2 library

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  pinMode(scrollButtonPin, INPUT_PULLUP);
  pinMode(selectButtonPin, INPUT_PULLUP);

  // Add this line to enable serial communication
  Serial.begin(9600);

  lcd.init();
  lcd.setBacklight(1);
  displayMenu();

  lcd.print("Hello");

}

void loop() {
  //none
}