# ESP32 firmware derleme ve cihaz kabulü

16 Ekim 2026’da ölçüm ve kalibrasyon programları GitHub Actions üzerinde ayrı işlerde başarıyla derlendi. Kaynak commit: `be77a5df68439dd15cb4578ae177907e4cd9fb9f`. [İki hedefin CI kaydı](https://github.com/busrabuseucar/foodcycle/actions/runs/38927848040).

## Tekrarlanabilir ortam

| Bileşen | Sabitlenen değer |
|---|---|
| PlatformIO Core | 6.1.18 |
| Espressif 32 platformu | 6.10.0 |
| Kart hedefi | esp32doit-devkit-v1 |
| Framework | Arduino; platformun çözümlediği ESP32 core 2.0.17 |
| HX711 kütüphanesi | bogde/HX711 0.7.5 |
| Seri haberleşme | 115200 baud |

Depo kökünde, ayrı Python sanal ortamında:

```sh
python -m pip install platformio==6.1.18
pio run -d firmware/FoodCycleAI_ESP32_HX711
pio run -d firmware/FoodCycleAI_HX711_Calibration
```

Her sketch kendi `platformio.ini` dosyasını kullanır. Kaynak filtresi hem Arduino `.ino` girdisini hem otomatik üretilen `.cpp` dosyasını kapsar; `.pio` derleme çıktıları kaynak kontrolüne alınmaz. CI iki hedefi bağımsız derler ve her biri için `firmware.bin` artefaktı saklar. Bu binary tek başına tüm flash yerleşimi değildir; kart yüklemesinde PlatformIO/Arduino’nun bootloader ve partition işlemlerini kullan.

İlk CI denemesinde kaynak filtresi oluşturulan C++ dosyasını dışladığı için “Nothing to build” hatası alındı. Filtre düzeltildi; sonraki iki derleme başarılı oldu. Testi atlama veya hata bastırma kullanılmadı. Yerel paralel denemede paket aynasının checksum doğrulaması başarısız oldu; bütünlük kontrolü gevşetilmedi ve yerel deneme başarı olarak raporlanmadı. Kanıt, yukarıdaki temiz CI derlemeleridir.

## Derleme ile fiziksel doğrulama ayrımı

Derleme; hedef mimari, sözdizimi, kütüphane API uyumu ve firmware çıktısının üretilebildiğini doğrular. Tartım doğruluğunu, kalibrasyon faktörünü, USB bağlantısını veya çalışma sırasında cihaz davranışını doğrulamaz. `-7050` örnek kalibrasyon faktörüdür; gerçek platforma özgü ölçüm sonucu değildir.

Fiziksel kabul için [bağlantı planını](01_BAGLANTI_PLANI.md) ve [test protokolünü](03_TEST_PROTOKOLU.md) uygula. Kart modeli/seri kimliği, sensör kapasitesi, referans kütleler, kalibrasyon faktörü, gram birimi, tekrar ölçümleri, tare sonrası beş örneklik stabilite, bağlantı kopması ve yeniden başlatma sonuçlarını kaydet. Üretim cihazına geçmeden uzun süreli drift ve arıza davranışı ayrıca sınanmalı. Bu çalışma sırasında fiziksel kart veya referans ağırlık erişimi yoktu.
