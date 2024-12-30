Konuşan Akıllı Bitki Bakım Robotu Proje Raporu

### Proje Amacı:

Bu projenin amacı, bitkilerin topraktaki nem ve su seviyelerini otomatik olarak takip eden, kullanıcıya hem görsel hem de sesli uyarılarla bilgi veren bir akıllı sistem tasarlamaktır. Sistem; toprağın kuru, nemli veya ıslak durumlarına göre gerçek zamanlı olarak bilgi sunarken, Thingspeak platformu üzerinden verileri anlık olarak izleme olanağı sağlar. Bu çözüm, bitki bakımını kolaylaştırmayı, verimliliği artırmayı ve bitki sağlığını optimize etmeyi hedefler.

### Proje Kapsamı:

-   Nem ve Su Seviyesi Takibi: Toprak nem seviyesinin ve su seviyesinin sensörlerle tespit edilmesi.
    
-   Görsel Bildirimler: LED ve LCD ekran kullanılarak nem ve su durumu bilgisinin aktarılması.
    
-   Thingspeak Entegrasyonu: Verilerin Thingspeak platformuna gönderimi ve Thingspeak API üzerinden anlık izleme.
    
-   Sesli Uyarı Sistemi: Python kodu kullanılarak toprağın durumuna göre sesli uyarılar verilmesi.
    

### Kullanılan Malzemeler:

-   ESP32: Wi-Fi bağlantısı ve Thingspeak entegrasyonu için.
    
-   3 Renk LED:
    

-   Kırmızı: Kuru toprağı belirtir.
    
-   Yeşil: Nemli toprağı belirtir.
    
-   Mavi: Islak toprağı belirtir.
    

-   Buzzer: Kritik durumlar için sesli uyarı sağlar.
    
-   Potansiyometre: LCD ekran parlaklığını ayarlamak için.
    
-   LCD Ekran: Nem seviyesi ve durum bilgilerini görselleştirir.
    
-   Su Sensörü: Su seviyesini ölçer ve Thingspeak'e veri gönderir.
    
-   Nem Sensörü: Toprağın nem seviyesini ölçerek durum bilgisini belirler.
