#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buttonPin = 2;

String symbols[] = {"7", "@", "#", "$", "%", "&"};

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(buttonPin, INPUT_PULLUP);

  randomSeed(analogRead(A0)); // better randomness

  lcd.setCursor(0, 0);
  lcd.print("Slot Machine!");
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    spin();

    while (digitalRead(buttonPin) == LOW); // wait for release
    delay(50); // debounce
  }
}

void spin() {
  lcd.clear();

  String s1, s2, s3;

  // spinning animation
  for (int i = 0; i < 10; i++) {
    s1 = symbols[random(0, 6)];
    s2 = symbols[random(0, 6)];
    s3 = symbols[random(0, 6)];

    lcd.setCursor(5, 0);
    lcd.print("|" + s1 + "|" + s2 + "|" + s3 + "|");

    delay(100 + i * 30); // slowing effect
  }

  // result
  lcd.setCursor(0, 1);

  if (s1 == s2 && s2 == s3) {
    lcd.print("!!!JACKPOT!!!");
  } 
  else if (s1 == s2 || s2 == s3 || s1 == s3) {
    lcd.print("YOU WIN!");
  } 
  else {
    lcd.print("YOU LOSE");
  }
}