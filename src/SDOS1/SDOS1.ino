#include <Arduino.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <WiFi.h>
#include <SpotifyEsp32.h>
#include <SPI.h>

//      1. PINES DEF
#define TFT_CS    5
#define TFT_RST   4
#define TFT_DC    2
#define TFT_MOSI  23  // SDI on screen
#define TFT_SCLK  18  // SCK on screen

//      2. CREDENTIALS
char* SSID = "Wifi_ppal";
char* PASSWORD = "clave463";
const char* CLIENT_ID = "94729e42a86840df9aa03baaaba1f6ac";
const char* CLIENT_SECRET = "e0700e68dc5e448f86d45531af322b4d";

//      3. OBJ CREATIONS
Spotify sp(CLIENT_ID, CLIENT_SECRET);
// Same pines above
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

String lastArtist;
String lastTrackname;

void setup() {
    Serial.begin(115200);

    // screen init
    tft.initR(INITR_BLACKTAB);
    tft.setRotation(1); // Horizontal mode
    tft.fillScreen(ST77XX_BLACK);
    Serial.println("TFT Initialized");

    // Connect Wifi
    WiFi.begin(SSID, PASSWORD);
    Serial.print("Connecting to WiFi...");
    while(WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected");

    // Show IP on screen test
    tft.setCursor(10, 10);
    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(1);
    tft.print("WiFi Okay");
    tft.setCursor(10, 25);
    tft.print(WiFi.localIP());

    // Authentificating Spotify
    sp.begin();
    Serial.println("Waiting authorization from Spotify...");
    while(!sp.is_auth()){
        sp.handle_client();
    }
    Serial.println("Spotify authorized!");
    tft.fillScreen(ST77XX_BLACK);
}

void loop() {
    // Data srch of Spotify
    String currentArtist = sp.current_artist_names();
    String currentTrackname = sp.current_track_name();

    // Screen refrech
    if (lastArtist != currentArtist && !currentArtist.isEmpty()) {
        tft.fillScreen(ST77XX_BLACK); // Clear screen
        lastArtist = currentArtist;
        
        tft.setCursor(10, 10);
        tft.setTextColor(ST77XX_CYAN);
        tft.setTextSize(2);
        tft.print(lastArtist);
    }

    if (lastTrackname != currentTrackname && currentTrackname != "null") {
        lastTrackname = currentTrackname;
        
        tft.setCursor(10, 50);
        tft.setTextColor(ST77XX_WHITE);
        tft.setTextSize(1);
        tft.print(lastTrackname);
    }

    delay(2000); // Wait 2 sec
}