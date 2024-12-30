import requests
import time
import pygame  # Ses çalma için kütüphane

# ThingSpeak API Bilgileri
READ_API_KEY = "XLTE289H3FKHRGHJ"  # ThingSpeak Read API Key
CHANNEL_ID = "2797072"  # ThingSpeak Kanal ID
URL = f"https://api.thingspeak.com/channels/{CHANNEL_ID}/feeds.json?api_key={READ_API_KEY}&results=1"

# Ses dosyaları
SOUNDS = {
    "dry": r"C:\Users\semsi\OneDrive\Masaüstü\Bitki-Bakim-Robotu,\dry_soil.mp3",
    "moist": r"C:\Users\semsi\OneDrive\Masaüstü\Bitki-Bakim-Robotu,\moist_soil.mp3",
    "wet": r"C:\Users\semsi\OneDrive\Masaüstü\Bitki-Bakim-Robotu,\wet_soil.mp3"
}


# Pygame başlat
pygame.mixer.init()

# Önceki durumun takibi
previous_state = None

while True:
    try:
        # ThingSpeak verilerini al
        response = requests.get(URL)
        data = response.json()
        print(f"ThingSpeak yanıtı: {data}")  # JSON yanıtını kontrol etmek için yazdır

        # JSON'dan field1 (Nem Seviyesi) ve field2 (Su Seviyesi) verilerini al
        feeds = data.get("feeds", [])
        if feeds:  # Eğer veri varsa
            soil_moisture = int(feeds[0].get("field1", 0))  # field1 (Nem Seviyesi)
            water_level = int(feeds[0].get("field2", 0))  # field2 (Su Seviyesi)

            print(f"Toprak Nemi: {soil_moisture}, Su Seviyesi: {water_level}")

            # Nem seviyesine göre durumu belirle
            if soil_moisture < 2200:
                state = "wet"
            elif 2200 <= soil_moisture < 3900:
                state = "moist"
            else:
                state = "dry"

            # Durum değiştiyse ilgili ses dosyasını çal
            if state != previous_state:
                print(f"Durum değişti: {state}. Ses çalınıyor...")
                pygame.mixer.music.load(SOUNDS[state])  # Uygun ses dosyasını yükle
                pygame.mixer.music.play()  # Ses dosyasını çal
                while pygame.mixer.music.get_busy():
                    time.sleep(0.1)  # Ses çalınırken bekle
                previous_state = state
        else:
            print("Veri alınamadı!")

    except Exception as e:
        print(f"Hata oluştu: {e}")

    time.sleep(2)  # 2 saniyede bir kontrol
