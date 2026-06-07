#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int startBtn = 2;
const int resetBtn = 3;

bool running = false;

unsigned long startTime = 0;
unsigned long elapsed = 0;

void setup() {
  pinMode(startBtn, INPUT_PULLUP);
  pinMode(resetBtn, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("STOPWATCH");
}

void loop() {

  // --- Start/Stop toggle ---
  if (digitalRead(startBtn) == LOW) {
    delay(25); // debounce
    if (running) {
      elapsed += millis() - startTime;
      running = false;
    } else {
      startTime = millis();
      running = true;
    }
    while(digitalRead(startBtn) == LOW); // wait release
  }

  // --- Reset ---
  if (digitalRead(resetBtn) == LOW) {
    delay(25);
    running = false;
    elapsed = 0;
    while(digitalRead(resetBtn) == LOW);
  }

  // --- Time calculation ---
  unsigned long current = elapsed;
  if (running) current += millis() - startTime;

  unsigned int ms = current % 1000;
  unsigned int sec = (current / 1000) % 60;
  unsigned int min = (current / 60000);

  // --- Display ---
  lcd.setCursor(0,1);
  char buf[17];
  sprintf(buf, "%02u:%02u:%03u", min, sec, ms);
  lcd.print(buf);
}
