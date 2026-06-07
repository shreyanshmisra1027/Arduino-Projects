#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buttonPin = 2;

unsigned long lastChange = 0;
const unsigned long interval = 5000; // 10 sec

int currentLine = 0;
bool lastButtonState = HIGH;

// 🔥 30 Motivational Lines
String quotes[] = {
  "Stay Hungry",
  "Stay Foolish",
  "Keep Grinding",
  "No Excuses",
  "Be Consistent",
  "Focus & Win",
  "Dream Big",
  "Work Hard",
  "Stay Sharp",
  "Never Quit",
  "Push Limits",
  "Think Bigger",
  "Start Now",
  "Stay Strong",
  "Be Relentless",
  "Earn It",
  "Make It Count",
  "One More Rep",
  "Stay Focused",
  "Win Today",
  "Rise & Grind",
  "Hustle Daily",
  "Be Fearless",
  "Act Now",
  "Keep Moving",
  "No Limits",
  "Stay Driven",
  "Go All In",
  "Trust Process",
  "Level Up"
};

const int totalQuotes = sizeof(quotes) / sizeof(quotes[0]);

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(buttonPin, INPUT_PULLUP);

  displayQuote();
}

void loop() {
  unsigned long currentMillis = millis();

  // ⏱ Auto change
  if (currentMillis - lastChange >= interval) {
    nextQuote();
    lastChange = currentMillis;
  }

  // 🔘 Button press
  bool buttonState = digitalRead(buttonPin);

  if (lastButtonState == HIGH && buttonState == LOW) {
    nextQuote();
    lastChange = currentMillis;
    delay(200); // debounce
  }

  lastButtonState = buttonState;
}

void nextQuote() {
  currentLine++;
  if (currentLine >= totalQuotes) {
    currentLine = 0;
  }
  displayQuote();
}

void displayQuote() {
  lcd.clear();

  String text = quotes[currentLine];

  // Center text (basic)
  int padding = (16 - text.length()) / 2;
  if (padding < 0) padding = 0;

  lcd.setCursor(padding, 0);
  lcd.print(text);

  lcd.setCursor(3, 1);
  lcd.print("SHREYANSH!");
}