#include <Servo.h>

Servo myServo;
int led = 5;

void setup() {
  myServo.attach(3);
  pinMode(led, OUTPUT);
}

void loop() {

  // Move from 0° to 180°
  for (int angle = 0; angle <= 180; angle++) {
    myServo.write(angle);

    if (angle == 0) {
      digitalWrite(led, HIGH);
    } else {
      digitalWrite(led, LOW);
    }

    delay(15);
  }

  // Move from 180° to 0°
  for (int angle = 180; angle >= 0; angle--) {
    myServo.write(angle);

    if (angle == 180) {
      digitalWrite(led, HIGH);
    } else {
      digitalWrite(led, LOW);
    }

    delay(15);
  }
}
