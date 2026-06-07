#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Button pins
#define BTN_MOVE 2
#define BTN_SELECT 3
#define BTN_LOCK 4

int cursor = 0;
int picks[4];
int pickCount = 0;

int bombs[4];

bool locked = false;
bool gameOver = false;

// Debounce
unsigned long resultStartTime = 0;
unsigned long lastPress = 0;
int debounceDelay = 200;

// ----------- SETUP -----------
void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(BTN_MOVE, INPUT_PULLUP);
  pinMode(BTN_SELECT, INPUT_PULLUP);
  pinMode(BTN_LOCK, INPUT_PULLUP);

  randomSeed(analogRead(A0));

  resetGame();
}

// ----------- MAIN LOOP -----------
void loop() {

  if (gameOver) {
    // Wait 5 seconds before allowing reset
    if (millis() - resultStartTime > 5000) {
       if (buttonPressed(BTN_LOCK)) {
         resetGame();
        }
    }
  return;
  }

  if (!locked) {

    if (buttonPressed(BTN_MOVE)) {
      cursor = (cursor + 1) % 16;
    }

    if (buttonPressed(BTN_SELECT)) {
      togglePick(cursor);
    }

    if (buttonPressed(BTN_LOCK) && pickCount == 4) {
      locked = true;
      revealBoard();
      delay(2000);
      showResult();

      resultStartTime = millis(); // ⏱️ start timer
      gameOver = true;
    }
  }

  drawScreen();
}

// ----------- GAME FUNCTIONS -----------

void resetGame() {
  cursor = 0;
  pickCount = 0;
  locked = false;
  gameOver = false;

  generateBombs();
  lcd.clear();
}

void generateBombs() {
  int count = 0;

  while (count < 4) {
    int r = random(0, 16);

    bool exists = false;
    for (int i = 0; i < count; i++) {
      if (bombs[i] == r) exists = true;
    }

    if (!exists) {
      bombs[count++] = r;
    }
  }
}

bool alreadyPicked(int pos) {
  for (int i = 0; i < pickCount; i++) {
    if (picks[i] == pos) return true;
  }
  return false;
}

// ⭐ NEW: Toggle selection
void togglePick(int pos) {

  // If already selected → remove it
  for (int i = 0; i < pickCount; i++) {
    if (picks[i] == pos) {

      // Shift left to remove
      for (int j = i; j < pickCount - 1; j++) {
        picks[j] = picks[j + 1];
      }

      pickCount--;
      return;
    }
  }

  // If not selected → add (if space available)
  if (pickCount < 4) {
    picks[pickCount++] = pos;
  }
}

bool isBomb(int pos) {
  for (int i = 0; i < 4; i++) {
    if (bombs[i] == pos) return true;
  }
  return false;
}

// ----------- DISPLAY -----------

void drawScreen() {
  lcd.setCursor(0, 0);

  for (int i = 0; i < 16; i++) {
    lcd.print((char)255); // blocks
  }

  lcd.setCursor(0, 1);

  for (int i = 0; i < 16; i++) {
    if (cursor == i) {
      lcd.print("^"); // cursor
    } else if (alreadyPicked(i)) {
      lcd.print("^"); // selected
    } else {
      lcd.print(" ");
    }
  }
}

void revealBoard() {
  lcd.clear();

  lcd.setCursor(0, 0);
  for (int i = 0; i < 16; i++) {
    if (isBomb(i)) {
      lcd.print("*");
    } else {
      lcd.print(" ");
    }
  }

  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    if (alreadyPicked(i)) {
      lcd.print("^");
    } else {
      lcd.print(" ");
    }
  }
}

void showResult() {
  int safe = 0;
  int hitBomb = 0;

  for (int i = 0; i < pickCount; i++) {
    if (isBomb(picks[i])) {
      hitBomb++;
    } else {
      safe++;
    }
  }

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Safe: ");
  lcd.print(safe);

  lcd.setCursor(0, 1);
  if (hitBomb > 0) {
    lcd.print("BOOM! ");
    lcd.print(hitBomb);
  } else {
    lcd.print("PERFECT!");
  }
}

// ----------- INPUT -----------

bool buttonPressed(int pin) {
  if (digitalRead(pin) == LOW) {
    if (millis() - lastPress > debounceDelay) {
      lastPress = millis();
      return true;
    }
  }
  return false;
}