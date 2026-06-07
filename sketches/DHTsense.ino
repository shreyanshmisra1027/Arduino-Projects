#include <DHT.h>;
#include <DHT_U.h>;
#define Type DHT22
int sensePin = 2;
DHT HT(sensePin, Type );
float tempC;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
HT.begin() ;
}

void loop() {
  // put your main code here, to run repeatedly:
tempC = HT.readTemperature();
Serial.println(tempC);
delay(1000);
}
