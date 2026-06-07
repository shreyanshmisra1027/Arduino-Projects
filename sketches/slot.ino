#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define BUTTON 2

const char* symbols[] = {"7", "A", "B", "C", "$"};
int s1, s2, s3;

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
}

void drawSlots() {
  display.clearDisplay();

  display.setCursor(10, 25);
  display.print(symbols[s1]);

  display.setCursor(55, 25);
  display.print(symbols[s2]);

  display.setCursor(100, 25);
  display.print(symbols[s3]);

  display.display();
}

void spinAnimation() {
  for (int i = 0; i < 20; i++) {
    s1 = random(5);
    s2 = random(5);
    s3 = random(5);

    drawSlots();
    delay(50 + i * 10); // slows down
  }
}

void loop() {
  if (digitalRead(BUTTON) == LOW) {
    spinAnimation();

    // Final result
    s1 = random(5);
    s2 = random(5);
    s3 = random(5);

    drawSlots();

    display.setTextSize(1);
    display.setCursor(30, 50);

    if (s1 == s2 && s2 == s3) {
      display.print("YOU WIN!");
    } else {
      display.print("TRY AGAIN");
    }

    display.display();

    delay(1500);
  }
}