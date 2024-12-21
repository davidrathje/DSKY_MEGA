#include <Keypad.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMPIXELS 25

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint32_t WHITE[] = { 6, 7, 8, 9, 14, 15, 16, 17, 20, 21, 22, 23 };
uint32_t YELLOW[] = { 0, 1, 2, 3, 4, 5, 10, 11, 12, 13, 18, 19, 20, 21, 24, 25 };

void powerLED() {
  for (int i : WHITE)
    pixels.setPixelColor(i, pixels.Color(100, 100, 50));
  for (int i : YELLOW)
    pixels.setPixelColor(i, pixels.Color(200, 200, 0));
  pixels.show();
}

const byte ROWS = 3;
const byte COLS = 7;

char dskyKeyboard[ROWS][COLS] = {
  { ' ', '+', '7', '8', '9', 'C', ' ' },
  { 'V', '-', '4', '5', '6', 'P', 'E' },
  { 'N', '0', '1', '2', '3', 'K', 'R' }
};

byte rowPins[ROWS] = { 53, 51, 49 };
byte colPins[COLS] = { 40, 42, 44, 46, 48, 50, 52 };

Keypad dskyKeys = Keypad(makeKeymap(dskyKeyboard), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  pixels.begin();
  pixels.setBrightness(150);
}

void loop() {
  pixels.clear();
  powerLED();

  if (Serial1.available() > 0)
    char(Serial.print(Serial1.read()));

  char key = dskyKeys.getKey();
  if (key) {
    Serial1.print(key);
  }
}