#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Bounce2.h> // Include the Bounce2 library
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int scrollButtonPin = 6;
const int selectButtonPin = 5;
const int auxButtonPin = 12;

String menuItems[] = {"Activate Fold", "Options"};
String optionItems[] = {"Raise Arms", "Re-Home Arms", "Credits", "Back <"};

int currentMenuItem = 0;
int currentOptionItem = 0;

int currentFrame = 0;

int foldingProgress = 0;

const long foldingInterval = 1500;
long timeSinceFold = 0;

Bounce scrollButton = Bounce(); // Instantiate a Bounce object
Bounce selectButton = Bounce();
Bounce auxButton = Bounce ();

Servo leftArm;
Servo rightArm;
Servo centerArm; 

byte Progress[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

void displayMenu() {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Foldamatics v1.0");

  for (int i = 0; i < (sizeof(menuItems) / sizeof(menuItems[0])); i++) {
    delay(10);
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
    delay(10);
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

void displayCredits() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ryan Dick");
  delay(10);
  lcd.setCursor(0, 3);
  lcd.print("> Back");
}

void runFold() {

  if (foldingProgress > 10){
      foldingProgress = 0;
  }

  switch (foldingProgress) {
    
    case 0:
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Folding in Progress:");
      lcd.setCursor(1, 1);
      lcd.print("[");
      lcd.setCursor(18, 1);
      lcd.print("]");
      lcd.setCursor(0, 3);
      lcd.print("> Stop Fold");

      //ADD FOLDING STEP

      timeSinceFold = millis();
      foldingProgress++;
      break;
    case 1:
      leftArm.write(142);

      timeSinceFold = millis();

      lcd.setCursor(2, 1);
      lcd.write(0);
      lcd.write(0);
       
      foldingProgress++;
      break;
    case 2:
      leftArm.write(21);

      timeSinceFold = millis();

      lcd.write(0);
      lcd.write(0);
      lcd.write(0);
       
      foldingProgress++;
      break;
    case 3:
      rightArm.write(170);
      timeSinceFold = millis();

      lcd.write(0);
      lcd.write(0);
       
      foldingProgress++;
      break;
    case 4:
      rightArm.write(36);
      timeSinceFold = millis();

      lcd.write(0);
      lcd.write(0);
      lcd.write(0);
       
      foldingProgress++;
      break;
    case 5:
      centerArm.write(180);
      timeSinceFold = millis();

      lcd.write(0);
      lcd.write(0);
       
      foldingProgress++;
      break;
    case 6:
      centerArm.write(65);
      timeSinceFold = millis();

      lcd.write(0);
      lcd.write(0);
      lcd.write(0);
       
      foldingProgress++;
      break;
    case 7:
      lcd.write(0);
      timeSinceFold = 0;

      tone(3, 500, 800);

      delay(1250);
       
      foldingProgress = 0;
      currentFrame = 0;
      
      displayMenu();
      break;
  }

}

void setup() {
  delay(1000);
  Wire.setClock(1000);

  lcd.createChar(0, Progress);
  
  leftArm.attach(7);
  rightArm.attach(8);
  centerArm.attach(9);

  leftArm.write(21);
  centerArm.write(65);
  rightArm.write(36);

  lcd.clear();
  pinMode(scrollButtonPin, INPUT_PULLUP);
  pinMode(selectButtonPin, INPUT_PULLUP);
  pinMode(auxButtonPin, INPUT_PULLUP);

  // Add this line to enable serial communication
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  displayMenu();

  scrollButton.attach(scrollButtonPin); // Attach the scrollButton to the Bounce object
  scrollButton.interval(20); // Set the debounce interval to 10 ms

  selectButton.attach(selectButtonPin);
  selectButton.interval(100);

  auxButton.attach(auxButtonPin);
  auxButton.interval(40);
}

void loop() {
  Serial.println(foldingProgress);
  Wire.setClock(1000);

  // Update the Bounce instance
  scrollButton.update();
  selectButton.update();
  auxButton.update();

  if (auxButton.fell()) {
    currentFrame = 3;
    runFold();  
  }

  // Check for a scrollButton press (when the scrollButton goes from HIGH to LOW)
  if (scrollButton.fell()) {

    // Add this line to print a message when the scrollButton is pressed
    tone(3, 200, 250);

    switch (currentFrame) {
      case 0:
        delay(250);
        currentMenuItem++;
        if (currentMenuItem >= (sizeof(menuItems) / sizeof(menuItems[0]))) {
          currentMenuItem = 0;
        }
        displayMenu();
        break;
      case 1:
        delay(250);
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
        delay(250);

        switch (currentMenuItem) {
          case 0:
            currentFrame = 3;
            runFold();
            break;
          case 1:
            currentFrame = 1;
            displayOptions();
        }
        break;
      case 1:
        delay(250);
        switch (currentOptionItem) {
          case 0:
            break;
          case 1:
            break;
          case 2:
            currentFrame = 2;
            displayCredits();
            break;
          case 3:
            currentFrame = 0;
            currentMenuItem = 0; 
            displayMenu();
        }
        break;
      case 2:
        delay(250);
        currentFrame = 1;
        currentOptionItem = 0; 
        displayOptions();
        delay(1000);
        break;
      case 3:
        foldingProgress = foldingProgress + 10;
        currentFrame = 0;
        currentMenuItem = 0; 
        displayMenu(); 
        break;
    }
  }

  if(foldingProgress > 0 && foldingProgress < 9 && ((millis() - timeSinceFold) > foldingInterval)) {
    tone(3, 400, 80);
    runFold();
  }

}


