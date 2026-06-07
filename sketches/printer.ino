#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  // put your setup code here, to run once:
lcd.init();
lcd.backlight();
lcd.clear();
lcd.setCursor(0,0);
}

void loop() {
  // put your main code here, to run repeatedly:
lcd.print("Ayo what's up?");
delay(1000);
lcd.clear();
lcd.print("@_@");
delay(800);
lcd.clear();
}
