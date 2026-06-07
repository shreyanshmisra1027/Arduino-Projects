#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------- Keypad ----------
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9,8,7,6};
byte colPins[COLS] = {5,4,3,2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ---------- Multi-tap maps ----------
String map2="ABC", map3="DEF", map4="GHI", map5="JKL";
String map6="MNO", map7="PQRS", map8="TUV", map9="WXYZ";

// ---------- State ----------
char lastKey = 0;
int tapIndex = 0;
unsigned long lastPressTime = 0;
unsigned long timeout = 900;

String sentence = "";
char previewChar = ' ';

// ---------- Helpers ----------
String getMap(char k) {
  switch(k) {
    case '2': return map2;
    case '3': return map3;
    case '4': return map4;
    case '5': return map5;
    case '6': return map6;
    case '7': return map7;
    case '8': return map8;
    case '9': return map9;
  }
  return "";
}

void refreshLCD() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(sentence);

  lcd.setCursor(0,1);
  lcd.print(">");
  lcd.print(previewChar);
}

// ---------- Setup ----------
void setup() {
  lcd.init();
  lcd.backlight();
  refreshLCD();
}

// ---------- Loop ----------
void loop() {
  char key = keypad.getKey();
  unsigned long now = millis();

  // reset tap cycle on timeout
  if (lastKey && now - lastPressTime > timeout) {
    lastKey = 0;
    tapIndex = 0;
  }

  if (!key) return;

  // ===== Multi-tap letters =====
  if (key >= '2' && key <= '9') {
    String m = getMap(key);

    if (key == lastKey)
      tapIndex = (tapIndex + 1) % m.length();
    else {
      tapIndex = 0;
      lastKey = key;
    }

    previewChar = m[tapIndex];
    lastPressTime = now;
    refreshLCD();
  }

  // ===== ENTER =====
  else if (key == 'A') {
    if (previewChar != ' ') {
      sentence += previewChar;
      previewChar = ' ';
      lastKey = 0;
      tapIndex = 0;
      refreshLCD();
    }
  }

  // ===== BACKSPACE =====
  else if (key == 'B') {
    if (sentence.length()) {
      sentence.remove(sentence.length()-1);
      refreshLCD();
    }
  }

  // ===== SPACE =====
  else if (key == 'C') {
    sentence += ' ';
    refreshLCD();
  }

  // ===== NUMBER MODE =====
  else if (key == 'D') {
    if (lastKey >= '0' && lastKey <= '9') {
      sentence += lastKey;
      previewChar = ' ';
      lastKey = 0;
      tapIndex = 0;
      refreshLCD();
    }
  }

  // ===== Direct numbers =====
  else if (key == '0' || key == '1') {
    sentence += key;
    refreshLCD();
  }

  // ===== Special characters =====
  else if (key == '#' || key == '*') {
    sentence += key;
    refreshLCD();
  }
}
