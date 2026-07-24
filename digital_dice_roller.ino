#include <LiquidCrystal.h>

// lcd pin configuration
const int rs = 12;
const int en = 11;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// button pin
const int buttonPin = 6;

// timing variables
unsigned long lastButtonTime = 0;
unsigned long rollingStartTime = 0;
boolean isRolling = false;
const int rollingDuration = 1000;  // 1 second
const int debounceDelay = 50;      // debounce

// dice result
int diceResult = 0;

void setup() {
  // initialize lcd
  lcd.begin(16, 2);
  
  // setup pins
  pinMode(buttonPin, INPUT_PULLUP);
  
  // startup msg
  lcd.print("Dice Roller");
  lcd.setCursor(0, 1);
  lcd.print("Press to roll!");
  delay(2000);
  lcd.clear();
}

void loop() {
  
  int buttonState = digitalRead(buttonPin);
  unsigned long currentTime = millis();
  
  
  if (buttonState == LOW && (currentTime - lastButtonTime) > debounceDelay) {
    lastButtonTime = currentTime;
    
    // start rolling
    isRolling = true;
    rollingStartTime = currentTime;
    
    // rolling message
    lcd.clear();
    lcd.print("Rolling...");
  }
  
  // rolling animation
  if (isRolling) {
    // check if rolling time is done
    if (currentTime - rollingStartTime > rollingDuration) {
      isRolling = false;
      
      // (1-6)
      diceResult = random(1, 7);
      
      
      lcd.clear();
      lcd.print("You rolled a ");
      lcd.print(diceResult);
      lcd.setCursor(0, 1);
      lcd.print("Press to roll!");
    }
  }
}
