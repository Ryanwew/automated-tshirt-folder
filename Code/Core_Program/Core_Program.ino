#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Bounce2.h> // Include the Bounce2 library

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int scrollButtonPin = 6;
const int selectButtonPin = 5;
String menuItems[] = {"Activate Fold", "Options"};
String optionItems[] = {"Raise Arms", "Credits", "Back <"};
int currentMenuItem = 0;
int currentOptionItem = 0;
int currentFrame = 0;

Bounce scrollButton = Bounce(); // Instantiate a Bounce object
Bounce selectButton = Bounce();

void displayMenu() {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Foldamatics v0.1");

  for (int i = 0; i < (sizeof(menuItems) / sizeof(menuItems[0])); i++) {
    lcd.setCursor(0, (i+2));
    if (i == currentMenuItem) {
      lcd.print("> ");
      lcd.print(menuItems[i]);
    } else {
      lcd.print("  ");
      lcd.print(menuItems[i]);
    }
  }
}

void displayOptions() {
  lcd.clear();

  for (int i = 0; i < (sizeof(optionItems) / sizeof(optionItems[0])); i++) {
    lcd.setCursor(0, (i));
    if (i == currentOptionItem) {
      lcd.print("> ");
      lcd.print(optionItems[i]);
    } else {
      lcd.print("  ");
      lcd.print(optionItems[i]);
    }
  }
}

void setup() {
  pinMode(scrollButtonPin, INPUT_PULLUP);
  pinMode(selectButtonPin, INPUT_PULLUP);

  // Add this line to enable serial communication
  Serial.begin(9600);

  lcd.init();
  lcd.setBacklight(1);
  displayMenu();

  scrollButton.attach(scrollButtonPin); // Attach the scrollButton to the Bounce object
  scrollButton.interval(20); // Set the debounce interval to 10 ms

  selectButton.attach(selectButtonPin);
  selectButton.interval(20);
}

void loop() {
  // Update the Bounce instance
  scrollButton.update();
  selectButton.update();

  // Check for a scrollButton press (when the scrollButton goes from HIGH to LOW)
  if (scrollButton.fell()) {

    // Add this line to print a message when the scrollButton is pressed
    Serial.println("Button pressed");
    tone(3, 200, 250);

    switch (currentFrame) {
      case 0:
        currentMenuItem++;
        if (currentMenuItem >= (sizeof(menuItems) / sizeof(menuItems[0]))) {
          currentMenuItem = 0;
        }
        displayMenu();
        break;
      case 1:
        currentOptionItem++;
        if (currentOptionItem >= (sizeof(optionItems) / sizeof(optionItems[0]))) {
          currentOptionItem = 0;
        }
        displayOptions();
        break;
      default:
        break; //maybe add an error screen here
    }
  }

  if (selectButton.fell()) {
    tone(3, 400, 400);

    switch (currentFrame) {
      case 0:
        switch (currentMenuItem) {
          case 0:
            break;
          case 1:
            currentFrame = 1;
            displayOptions();
        }
        break;
      case 1:
        break;
    }
  }

}


