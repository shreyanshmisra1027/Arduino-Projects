#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // change to 0x3F if needed

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'.','0','#','D'}   // changed * to '.' for decimal
};

byte rowPins[ROWS] = {9,8,7,6};
byte colPins[COLS] = {5,4,3,2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

float num1 = 0;
float num2 = 0;
char op = 0;
bool secondNumber = false;

String input1 = "";
String input2 = "";

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.print("Calculator");
  delay(1000);
  lcd.clear();
}

void loop() {
  char key = keypad.getKey();
  if (!key) return;

  // Numbers and decimal
  if ((key >= '0' && key <= '9') || key == '.') {
    if (!secondNumber) {
      input1 += key;
      lcd.print(key);
    } else {
      input2 += key;
      lcd.print(key);
    }
  }

  // Operators
  if (key == 'A' || key == 'B' || key == 'C' || key == 'D') {
    if (input1.length() == 0) return;

    op = key;
    secondNumber = true;

    lcd.print(" ");
    lcd.print(opChar(op));
    lcd.print(" ");
  }

  // Equals
  if (key == '#') {
    if (input1.length() == 0 || input2.length() == 0) return;

    num1 = input1.toFloat();
    num2 = input2.toFloat();

    lcd.setCursor(0,1);

    if (op == 'D' && num2 == 0) {
      lcd.print("Error: Div by 0");
    } else {
      float result = calculate();
      lcd.print("= ");
      lcd.print(result, 4); // 4 decimal places
    }

    delay(3000);
    lcd.clear();
    resetCalc();
  }

  // Clear (use long press reset behavior if needed)
}

char opChar(char k){
  if(k=='A') return '+';
  if(k=='B') return '-';
  if(k=='C') return '*';
  if(k=='D') return '/';
  return '?';
}

float calculate() {
  switch(op) {
    case 'A': return num1 + num2;
    case 'B': return num1 - num2;
    case 'C': return num1 * num2;
    case 'D': return num1 / num2;
  }
  return 0;
}

void resetCalc(){
  input1 = "";
  input2 = "";
  num1 = 0;
  num2 = 0;
  op = 0;
  secondNumber = false;
}
