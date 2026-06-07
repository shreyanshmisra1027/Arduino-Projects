#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <time.h>

// LCD (change 0x27 if needed)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// NTP settings (India)
const char* ntpServer = "pool.ntp.org";
long gmtOffset_sec = 19800;   // IST = UTC+5:30
int daylightOffset_sec = 0;

void setup() {
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();

  lcd.print("Connecting...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  lcd.clear();
  lcd.print("Connected!");
  delay(1000);

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop() {
  struct tm timeinfo;

  if (getLocalTime(&timeinfo)) {
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Time:");

    lcd.setCursor(0, 1);
    lcd.printf("%02d:%02d:%02d",
      timeinfo.tm_hour,
      timeinfo.tm_min,
      timeinfo.tm_sec);
  }

  delay(1000);
}