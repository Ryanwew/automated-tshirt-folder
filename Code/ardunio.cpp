#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int buttonPin = 2;
const int debounceTime = 200; // Debounce time in milliseconds
int buttonState;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;

String menuItems[] = {"Start", "Menu", "Option", "Setting"};
int currentMenuItem = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  
  lcd.init();
  lcd.backlight();
  displayMenu();
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceTime) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        currentMenuItem++;
        if (currentMenuItem >= (sizeof(menuItems) / sizeof(menuItems[0]))) {
          currentMenuItem = 0;
        }
        displayMenu();
      }
    }
  }

  lastButtonState = reading;
}

void displayMenu() {
  lcd.clear();
  for (int i = 0; i < (sizeof(menuItems) / sizeof(menuItems[0])); i++) {
    lcd.setCursor(0, i);
    if (i == currentMenuItem) {
      lcd.print("> ");
      lcd.print(menuItems[i]);
    } else {
      lcd.print("  ");
      lcd.print(menuItems[i]);
    }
  }
}


// test it with something basic to make sure it is working and not a software issue 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 or 0x3F depending on your display
// 16 = number of columns, 2 = number of rows
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  // Initialize the LCD
  lcd.init();
  // Turn on the backlight
  lcd.backlight();

  // Set the cursor to the first column and first row
  lcd.setCursor(0, 0);
  // Print "Hello, World!" on the LCD
  lcd.print("Hello, World!");
}

void loop() {
  // No code needed in the loop for this basic example
}


// code for debugging
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int buttonPin = 2;
const int debounceTime = 200; // Debounce time in milliseconds
int buttonState;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;

String menuItems[] = {"Start", "Menu", "Option", "Setting"};
int currentMenuItem = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  // Add this line to enable serial communication
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  displayMenu();
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceTime) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        // Add this line to print a message when the button is pressed
        Serial.println("Button pressed");

        currentMenuItem++;
        if (currentMenuItem >= (sizeof(menuItems) / sizeof(menuItems[0]))) {
          currentMenuItem = 0;
        }
        displayMenu();
      }
    }
  }

  lastButtonState = reading;
}

void displayMenu() {
  lcd.clear();
  for (int i = 0; i < (sizeof(menuItems) / sizeof(menuItems[0])); i++) {
    lcd.setCursor(0, i);
    if (i == currentMenuItem) {
      lcd.print("> ");
      lcd.print(menuItems[i]);
    } else {
      lcd.print("  ");
      lcd.print(menuItems[i]);
    }
  }
}


// try this code please
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Bounce2.h> // Include the Bounce2 library

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int buttonPin = 2;
String menuItems[] = {"Start", "Menu", "Option", "Setting"};
int currentMenuItem = 0;

Bounce button = Bounce(); // Instantiate a Bounce object

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  // Add this line to enable serial communication
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  displayMenu();

  button.attach(buttonPin); // Attach the button to the Bounce object
  button.interval(10); // Set the debounce interval to 10 ms
}

void loop() {
  // Update the Bounce instance
  button.update();

  // Check for a button press (when the button goes from HIGH to LOW)
  if (button.fell()) {
    // Add this line to print a message when the button is pressed
    Serial.println("Button pressed");

    currentMenuItem++;
    if (currentMenuItem >= (sizeof(menuItems) / sizeof(menuItems[0]))) {
      currentMenuItem = 0;
    }
    displayMenu();
  }
}

void displayMenu() {
  lcd.clear();
  for (int i = 0; i < (sizeof(menuItems) / sizeof(menuItems[0])); i++) {
    lcd.setCursor(0, i);
    if (i == currentMenuItem) {
      lcd.print("> ");
      lcd.print(menuItems[i]);
    } else {
      lcd.print("  ");
      lcd.print(menuItems[i]);
    }
  }
}
