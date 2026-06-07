#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(9);
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  int buttonState = digitalRead(2);

  if (buttonState == HIGH) {      // Button pressed
    myServo.write(90);
  } else {                       // Button released
    myServo.write(0);
  }

  delay(20); // small delay to reduce jitter
}
