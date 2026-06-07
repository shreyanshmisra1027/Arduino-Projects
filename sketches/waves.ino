#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// 8 fill levels
byte levels[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,31},
  {0,0,0,0,0,0,31,31},
  {0,0,0,0,0,31,31,31},
  {0,0,0,0,31,31,31,31},
  {0,0,0,31,31,31,31,31},
  {0,0,31,31,31,31,31,31},
  {0,31,31,31,31,31,31,31}
};

float t = 0;

void setup() {
  lcd.init();
  lcd.backlight();

  for (int i = 0; i < 8; i++) {
    lcd.createChar(i, levels[i]);
  }
}

void loop() {
  for (int x = 0; x < 16; x++) {

    // 🌊 Combine multiple waves (this is the magic)
    float y =
      sin(x * 0.4 + t) +
      0.5 * sin(x * 0.7 + t * 1.3) +
      0.3 * sin(x * 1.1 + t * 0.7);

    // Normalize roughly to -1 to +1
    y = y / 1.8;

    // Map to total height (0–15)
    int h = map(y * 100, -100, 100, 0, 15);

    int bottom = 0;
    int top = 0;

    if (h < 8) {
      bottom = h;
      top = 0;
    } else {
      bottom = 7;        // full bottom (water body)
      top = h - 8;       // wave above
    }

    // Draw bottom (water base)
    lcd.setCursor(x, 1);
    lcd.write(bottom);

    // Draw top (wave crest)
    lcd.setCursor(x, 0);
    lcd.write(top);
  }

  t += 0.15;  // speed
  delay(80);
}