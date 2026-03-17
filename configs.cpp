#include <TFT_eSPI.h>

#define FAN_PIN 26
#define TOUCH_PIN T0

TFT_eSPI tft = TFT_eSPI();
bool fanOn = false;

void drawUI() {
  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(3);
  tft.setCursor(40, 40);
  tft.println("Luefter Steuerung");

  tft.fillRoundRect(60, 150, 200, 80, 10,
                    fanOn ? TFT_GREEN : TFT_RED);

  tft.setTextColor(TFT_BLACK);
  tft.setCursor(110, 180);
  tft.println(fanOn ? "AN" : "AUS");
}

void setup() {
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);

  tft.init();
  tft.setRotation(1);
  drawUI();
}

void loop() {
  int touchValue = touchRead(TOUCH_PIN);

  if (touchValue < 30) {   // Schwelle ggf. anpassen
    fanOn = !fanOn;
    digitalWrite(FAN_PIN, fanOn ? HIGH : LOW);
    drawUI();
    delay(500); // Entprellen
  }
}
