#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_CS   5
#define TFT_DC   4
#define TFT_RST  2
#define POT_PIN  34

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

int ultimoValor = -1;

void setup() {
  Serial.begin(115200);
  tft.begin();
  tft.setRotation(1); 
  tft.fillScreen(ILI9341_BLACK);
  
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2); 
  tft.setCursor(10, 10);
  tft.print("Spotify Test");

  tft.setTextColor(ILI9341_LIGHTGREY);
  tft.setTextSize(2); 
  tft.setCursor(10, 45);
  tft.print("By Vinchy007");
}

void loop() {
  int valorPot = analogRead(POT_PIN);
  int valorAMostrar = map(valorPot, 0, 4095, 0, 100);

  if (valorAMostrar != ultimoValor) {
    tft.fillRect(10, 80, 180, 70, ILI9341_BLACK); 
    
    tft.setCursor(15, 85); 
    tft.setTextSize(6); 
    tft.setTextColor(ILI9341_GREEN);
    tft.print(valorAMostrar);
    
    ultimoValor = valorAMostrar;
    Serial.println(valorAMostrar);
  }
  delay(10); 
}