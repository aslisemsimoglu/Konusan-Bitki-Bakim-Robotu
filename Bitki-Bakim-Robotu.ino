#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD ekran ayarı
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Wi-Fi Bilgileri
#define WIFI_SSID "ASLI ŞEMŞİMOĞLU"
#define WIFI_PASSWORD "asli1903"

// Thingspeak API Bilgileri
#define THINGSPEAK_API_KEY "KB6R9FA25OO05DNQ"  // Thingspeak Write API Key
#define THINGSPEAK_URL "http://api.thingspeak.com/update"

// Pin Tanımları
#define SOIL_SENSOR_PIN 36 // Toprak nem sensörü
#define WATER_SENSOR_PIN 34 // Su sensörü
#define RED_LED 25         // Kırmızı LED
#define GREEN_LED 27       // Yeşil LED
#define BLUE_LED 26        // Mavi LED
#define BUZZER_PIN 33      // Buzzer

int prevSoilState = -1; // Önceki toprak durumu

// Toprak nem seviyesi okuma
int readSoilMoisture() {
  int total = 0;
  for (int i = 0; i < 10; i++) {
    total += analogRead(SOIL_SENSOR_PIN);
    delay(10);
  }
  return total / 10;
}

// Su seviyesi okuma
int readWaterLevel() {
  int total = 0;
  for (int i = 0; i < 10; i++) {
    total += analogRead(WATER_SENSOR_PIN);
    delay(10);
  }
  return total / 10;
}

void setup() {
  pinMode(SOIL_SENSOR_PIN, INPUT);
  pinMode(WATER_SENSOR_PIN, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(115200);

  // LCD ekran başlat
  lcd.init();
  lcd.backlight();

  // Wi-Fi bağlantısı
  Serial.print("Wi-Fi'ye bağlanılıyor...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi bağlantısı başarılı!");
  lcd.clear();
  lcd.print("Wi-Fi Baglandi");
}

void loop() {
  int soilMoisture = readSoilMoisture(); // Toprak nemi oku
  int waterLevel = readWaterLevel();    // Su seviyesi oku
  int soilState;

  // Nem seviyesine göre durumu belirle
  if (soilMoisture < 2200) {
    soilState = 2; // Çok sulu
  } else if (soilMoisture >= 2200 && soilMoisture < 3900) {
    soilState = 1; // Nemli
  } else {
    soilState = 0; // Kuru
  }

  // LCD ekran güncellemesi
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nem Orani: ");
  lcd.print(soilMoisture);
  lcd.setCursor(0, 1);

  if (soilState == 0) {
    lcd.print("Durum: COK KURU!");
  } else if (soilState == 1) {
    lcd.print("Durum: NEMLI   ");
  } else {
    lcd.print("Durum: COK ISLAK");
  }

  // LED ve buzzer kontrolü
  if (soilState != prevSoilState) {
    if (soilState == 0) {
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(BLUE_LED, LOW);
      digitalWrite(BUZZER_PIN, HIGH);
      Serial.println("DRY");
    } else if (soilState == 1) {
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(BLUE_LED, LOW);
      digitalWrite(BUZZER_PIN, LOW);
      Serial.println("MOIST");
    } else {
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(BLUE_LED, HIGH);
      digitalWrite(BUZZER_PIN, LOW);
      Serial.println("WET");
    }

    prevSoilState = soilState;
  }

  // Su seviyesi kontrolü
  Serial.print("Su Seviyesi: ");
  Serial.println(waterLevel);

  // Thingspeak'e veri gönderimi
  HTTPClient http;
  String url = THINGSPEAK_URL;
  url += "?api_key=" + String(THINGSPEAK_API_KEY);
  url += "&field1=" + String(soilMoisture); // Nem seviyesi
  url += "&field2=" + String(waterLevel);  // Su seviyesi

  http.begin(url);
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    Serial.print("Thingspeak'e veri gönderildi. HTTP Kodu: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.print("Thingspeak'e veri gönderme hatası. HTTP Hatası: ");
    Serial.println(httpResponseCode);
  }
  http.end();

  delay(2000); // 2 saniyede bir güncelle
}
