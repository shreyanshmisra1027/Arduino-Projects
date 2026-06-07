#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Buttons
const int btnSelect = 2;
const int btnIncrement = 3;

// Time
int hours = 12;
int minutes = 0;
int seconds = 0;

// Timing
unsigned long lastSecondTick = 0;

// Modes
bool settingMode = false;
int field = 0; // 0=H, 1=M, 2=S

// Timeout
unsigned long lastInteraction = 0;
const unsigned long timeout = 5000;

// Quote (16 chars)
String quote = "Own every second";

// Button states
bool lastSelectState = HIGH;
bool lastIncrementState = HIGH;

// Blink
bool blinkState = true;
unsigned long lastBlink = 0;

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(btnSelect, INPUT_PULLUP);
  pinMode(btnIncrement, INPUT_PULLUP);

  lcd.setCursor(0, 0);
  lcd.print(quote);
}

void loop() {
  handleButtons();

  if (!settingMode) {
    updateTime();
  }

  handleBlink();
  displayTime();
}

// ---------- TIME ----------
void updateTime() {
  if (millis() - lastSecondTick >= 1000) {
    lastSecondTick += 1000;
    seconds++;

    if (seconds >= 60) {
      seconds = 0;
      minutes++;
    }
    if (minutes >= 60) {
      minutes = 0;
      hours++;
    }
    if (hours >= 24) {
      hours = 0;
    }
  }
}

// ---------- BUTTONS ----------
void handleButtons() {
  bool selectState = digitalRead(btnSelect);
  bool incrementState = digitalRead(btnIncrement);

  // SELECT button
  if (lastSelectState == HIGH && selectState == LOW) {
    if (!settingMode) {
      settingMode = true;   // enter setting mode
      field = 0;
    } else {
      field = (field + 1) % 3;
    }
    lastInteraction = millis();
    delay(150);
  }

  // INCREMENT button
  if (lastIncrementState == HIGH && incrementState == LOW) {
    if (settingMode) {
      if (field == 0) hours = (hours + 1) % 24;
      if (field == 1) minutes = (minutes + 1) % 60;
      if (field == 2) seconds = (seconds + 1) % 60;

      lastInteraction = millis();
    }
    delay(150);
  }

  lastSelectState = selectState;
  lastIncrementState = incrementState;

  // Timeout exit
  if (settingMode && (millis() - lastInteraction > timeout)) {
    settingMode = false;
  }
}

// ---------- BLINK ----------
void handleBlink() {
  if (millis() - lastBlink >= 500) {
    lastBlink = millis();
    blinkState = !blinkState;
  }
}

// ---------- DISPLAY ----------
void displayTime() {
  char buffer[17];

  int ms = millis() % 1000;

  // Prepare strings
  char h[3], m[3], s[3], n[4];
  sprintf(h, "%02d", hours);
  sprintf(m, "%02d", minutes);
  sprintf(s, "%02d", seconds);
  sprintf(n, "%03d", ms);

  // Blink selected field
  if (settingMode && !blinkState) {
    if (field == 0) strcpy(h, "  ");
    if (field == 1) strcpy(m, "  ");
    if (field == 2) strcpy(s, "  ");
  }

  sprintf(buffer, "%s:%s:%s:%s", h, m, s, n);

  lcd.setCursor(0, 1);
  lcd.print(" "); // center padding
  lcd.print(buffer);
}