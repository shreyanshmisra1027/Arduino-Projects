#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>

// TFT pins
#define TFT_CS   5
#define TFT_DC   2
#define TFT_RST  4

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// Joystick
#define JOY_X 34
#define JOY_Y 35
#define BTN   25

int x = 120;
int y = 160;

bool penDown = true;
bool lastBtnState = HIGH;

void setup() {
  Serial.begin(115200);

  pinMode(BTN, INPUT_PULLUP);

  tft.begin();
  tft.setRotation(1); // landscape
  tft.fillScreen(ILI9341_BLACK);
}

void loop() {
  int joyX = analogRead(JOY_X);
  int joyY = analogRead(JOY_Y);

  int dx = 0, dy = 0;

  // Deadzone tuning (ESP32 ADC ~0–4095)
  if (joyX < 1400) dx = -2;
  else if (joyX > 2600) dx = 2;

  if (joyY < 1400) dy = 2;
  else if (joyY > 2600) dy = -2;

  int newX = constrain(x + dx, 0, 319);
  int newY = constrain(y + dy, 0, 239);

  // Button toggle
  bool btnState = digitalRead(BTN);
  if (btnState == LOW && lastBtnState == HIGH) {
    penDown = !penDown;
    delay(200);
  }
  lastBtnState = btnState;

  // Draw
  if (penDown) {
    tft.drawLine(x, y, newX, newY, ILI9341_WHITE);
  }

  x = newX;
  y = newY;

  delay(10);
}