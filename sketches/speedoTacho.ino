#include <Servo.h>

Servo myServo;

int potPin = A0;
int red = 1;
int yellow = 2;
int green = 3;

void setup() {
  myServo.attach(9);

  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
}

void loop() {
  int potValue = analogRead(potPin);

  // Map potentiometer to 0–180 degrees
  int angle = map(potValue, 0, 1023, 0, 180);

  myServo.write(angle);

  if (angle <= 60) {
    digitalWrite(green, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
  }
  else if (angle > 60 && angle <= 120) {
    digitalWrite(green, LOW);
    digitalWrite(yellow, HIGH);
    digitalWrite(red, LOW);
  }
  else {
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
  }

  delay(15);  // smooth movement
}
