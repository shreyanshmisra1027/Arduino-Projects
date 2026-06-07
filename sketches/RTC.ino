#include <Wire.h>
#include <RTClib.h>
#include <TM1637Display.h>

#define CLK 2
#define DIO 3

TM1637Display display(CLK, DIO);
RTC_DS1307 rtc;

void setup() {
  Wire.begin();
  display.setBrightness(7);

  if (!rtc.begin()) {
    while (1);
  }

  // Uncomment once to set RTC to compile time
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  DateTime now = rtc.now();

  int hours = now.hour();
  int minutes = now.minute();

  int timeDisplay = hours * 100 + minutes;

  // show colon blinking every second
  bool colon = now.second() % 2;
  display.showNumberDecEx(timeDisplay, colon ? 0b01000000 : 0, true);

  delay(500);
}
