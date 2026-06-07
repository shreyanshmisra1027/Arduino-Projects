int redPin = 9;
int greenPin = 10;
int bluePin = 11;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(9600);
  Serial.println("Type: R G B Y C M W O");
}

void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();

    if (c == 'R' || c == 'r') {
      analogWrite(redPin, 255);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
    }

    else if (c == 'G' || c == 'g') {
      analogWrite(redPin, 0);
      analogWrite(greenPin, 255);
      analogWrite(bluePin, 0);
    }

    else if (c == 'B' || c == 'b') {
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 255);
    }

    else if (c == 'Y' || c == 'y') { // Yellow
      analogWrite(redPin, 255);
      analogWrite(greenPin, 255);
      analogWrite(bluePin, 0);
    }

    else if (c == 'C' || c == 'c') { // Cyan
      analogWrite(redPin, 0);
      analogWrite(greenPin, 255);
      analogWrite(bluePin, 255);
    }

    else if (c == 'M' || c == 'm') { // Magenta
      analogWrite(redPin, 255);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 255);
    }

    else if (c == 'W' || c == 'w') { // White
      analogWrite(redPin, 255);
      analogWrite(greenPin, 255);
      analogWrite(bluePin, 255);
    }

    else if (c == 'O' || c == 'o') { // Off
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
    }
  }
}
