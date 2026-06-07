// ===== PWM PINS (RGB LED) =====
const int RED_LED   = 9;
const int GREEN_LED = 10;
const int BLUE_LED  = 11;

// ===== ANALOG INPUTS (POTENTIOMETERS) =====
// Matches your Wokwi wiring
const int RED_POT   = A1;   // pot2
const int GREEN_POT = A2;   // pot3
const int BLUE_POT  = A3;   // pot1

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // ----- Read raw ADC values (0–1023 ONLY) -----
  int redRaw   = analogRead(RED_POT);
  int greenRaw = analogRead(GREEN_POT);
  int blueRaw  = analogRead(BLUE_POT);

  // ----- Convert safely to PWM (0–255) -----
  int redPWM   = map(redRaw,   0, 1023, 0, 255);
  int greenPWM = map(greenRaw, 0, 1023, 0, 255);
  int bluePWM  = map(blueRaw,  0, 1023, 0, 255);

  // ----- Clamp values (extra safety) -----
  redPWM   = constrain(redPWM,   0, 255);
  greenPWM = constrain(greenPWM, 0, 255);
  bluePWM  = constrain(bluePWM,  0, 255);

  // ----- COMMON ANODE RGB LED → INVERT PWM -----
  analogWrite(RED_LED,   255 - redPWM);
  analogWrite(GREEN_LED, 255 - greenPWM);
  analogWrite(BLUE_LED,  255 - bluePWM);

  // ----- Serial output (NEVER negative) -----
  Serial.print("R:");
  Serial.print(redPWM);
  Serial.print(" G:");
  Serial.print(greenPWM);
  Serial.print(" B:");
  Serial.println(bluePWM);

  delay(20); // Stable, smooth readings
}
