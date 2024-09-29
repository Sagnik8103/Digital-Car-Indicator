#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int ADXL345 = 0x53;
float X_out, Y_out, Z_out;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int ledPin1 = 12;
const int ledPin2 = 13;
const int buzzerPin = 11;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.init();
  lcd.clear();
  lcd.backlight();

  lcd.setCursor(2, 0);
  lcd.print("Hello World");

  lcd.setCursor(2, 1);
  lcd.print("Auto Signal");

  byte rightArrow[8] = {
    B00000,
    B00001,
    B00011,
    B00111,
    B01111,
    B00111,
    B00011,
    B00001
  };
  byte leftArrow[8] = {
    B00000,
    B10000,
    B11000,
    B11100,
    B11110,
    B11100,
    B11000,
    B10000
  };
  
  lcd.createChar(0, rightArrow);
  lcd.createChar(1, leftArrow);

  Wire.beginTransmission(ADXL345);
  Wire.write(0x2D);
  Wire.write(8);
  Wire.endTransmission();
  delay(2000);
}

void loop() {
  lcd.clear();
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);

  Wire.beginTransmission(ADXL345);
  Wire.write(0x32);
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true);

  X_out = (Wire.read() | Wire.read() << 8);
  X_out = X_out / 256;
  Y_out = (Wire.read() | Wire.read() << 8);
  Y_out = Y_out / 256;
  Z_out = (Wire.read() | Wire.read() << 8);
  Z_out = Z_out / 256;

  if (Y_out < -0.50) {
    Serial.println("Tilted Right");
    displayLeftArrow();
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin1, LOW);
    tone(buzzerPin, 1000);
    delay(500);
    noTone(buzzerPin);
  } else if (Y_out > 0.50) {
    Serial.println("Tilted Left");
    displayRightArrow();
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
    tone(buzzerPin, 1000);
    delay(500);
    noTone(buzzerPin);
  } else {
    Serial.println("No significant tilt detected");
    lcd.setCursor(5, 0);
    lcd.print("No Tilt");
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    noTone(buzzerPin);
  }

  Serial.print("Xa= ");
  Serial.print(X_out);
  Serial.print("   Ya= ");
  Serial.print(Y_out);
  Serial.print("   Za= ");
  Serial.println(Z_out);

  delay(500);
}

void displayRightArrow() {
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("LEFT");
  for (int i = 0; i < 4; i++) {
    lcd.setCursor(i, 0);
    lcd.write(byte(0));
    lcd.setCursor(i, 1);
    lcd.write(byte(0));
  }
}

void displayLeftArrow() {
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("RIGHT");
  for (int i = 0; i < 4; i++) {
    lcd.setCursor(15 - i, 0);
    lcd.write(byte(1));
    lcd.setCursor(15 - i, 1);
    lcd.write(byte(1));
  }
}