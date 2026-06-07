#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int x = 0;
int y = 0;

int dx = 2;   // speed in x
int dy = 2;   // speed in y

int textSize = 2;
int textWidth = 3 * 6 * textSize;   // 3 letters * 6px default width
int textHeight = 8 * textSize;

void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;);
  }

  display.setTextSize(textSize);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {

  display.clearDisplay();

  display.setCursor(x, y);
  display.print("DVD");
  display.display();

  // Move
  x += dx;
  y += dy;

  // Bounce horizontally
  if (x <= 0 || x + textWidth >= SCREEN_WIDTH) {
    dx = -dx;
  }

  // Bounce vertically
  if (y <= 0 || y + textHeight >= SCREEN_HEIGHT) {
    dy = -dy;
  }

  delay(20);
}