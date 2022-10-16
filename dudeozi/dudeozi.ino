#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>
#define PIN 11
#define NUMPIXELS 9
#define BRIGHTNESS 180

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
LiquidCrystal_I2C lcd(16, 2, 0x27);

const int srtBtn = 13;  //start button
int srtVal;  //start button value
const int buzPin = 12;  //buzzer pin
int btn[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};  //button pin array
int ranVal = 0;  //random value
int ending = 1;  //quit game
int life = 0;  //life
int score = 0;  //score = score * 10
int bestScore = 0;  //best score

void dudeozi();

void setup() {
  Serial.begin(9600);

  pinMode(srtBtn, INPUT_PULLUP);
  pinMode(buzPin, OUTPUT);
  for (int i = 0; i<9; i++) {
    pinMode(btn[i], INPUT_PULLUP);
  }

  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show();
  lcd.init();
  lcd.backlight();
  lcd.print("ready");
  Serial.println("ready");
}

void loop() {
  srtVal = digitalRead(srtBtn);

  if (ending == 1) {
    if (srtVal == 0) {  //start game
      ending = 0;
      score = 0;
      life = 3;
      lcd.setCursor(5, 0);
      lcd.print("Start!");
      Serial.println("Start!");
      tone(buzPin, 880);
      delay(200);
      tone(buzPin, 932.33);
      delay(200);
      noTone(buzPin);
      delay(600);
      lcd.clear();
    }
  } else if (life == 0) {  //end game when life=0
    if (score > bestScore) {
      bestScore = score;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Now Best Score");
      lcd.setCursor(1, 1);
      lcd.print("Best Score:");
      lcd.print(bestScore);
      delay(1000);
    }
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("Game End");
    lcd.setCursor(1, 1);
    lcd.print("Best Score:");
    lcd.print(bestScore);
    Serial.println("Game End");
    Serial.print("Best Score:");
    Serial.println(bestScore);
    tone(buzPin, 523);  
    delay(800);
    noTone(buzPin);
    ending = 1;
    Serial.println();
    lcd.clear();
    lcd.setCursor(1, 1);
    lcd.print("Best Score:");
    lcd.print(bestScore);
  } else {  //play game when ending=0
    ranVal = getTrueRotateRandomByte() % 9;  //random number 0~8
    dudeozi();
  }
  delay(600);  //delay for next one
}

void dudeozi() {
  for (int cnt=0; cnt < 10; cnt++) {
    if (life == 0) {
      break;
    } else if (digitalRead(btn[ranVal]) == 0) {
      strip.setPixelColor(ranVal, 0, 0, 0);
      strip.show();
      tone(buzPin, 440);
      delay(50);
      noTone(buzPin);
      delay(50);
      tone(buzPin, 440);
      delay(50);
      noTone(buzPin);
      delay(50);
      tone(buzPin, 523);
      delay(200);
      noTone(buzPin);
      score += 10;
      life++;
      break;
    } else {
      strip.setPixelColor(ranVal, 0, 127, 0, 0);
      strip.show();
      Serial.println(ranVal);
      delay(50);
      strip.setPixelColor(ranVal, 0, 0, 0);
      strip.show();
    }
  }
  life--;
  Serial.println(life);
  lcd.setCursor(5, 0);
  lcd.print("life:");
  lcd.print(life);
  Serial.print("score:");
  Serial.println(score);
  lcd.setCursor(3, 0);
  lcd.print("score:");
  lcd.print(score);
}