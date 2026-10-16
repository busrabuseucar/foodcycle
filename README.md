# FoodCycle — Gıda Atığı Ölçüm ve Karar Destek Prototipi

Toplu yemek servislerinde atık tartımlarını kaydeden, servis başına kişi sayısıyla normalize eden ve operatöre açık kurallı karar desteği sunan HTML/CSS/JavaScript uygulaması. ESP32 + HX711 için Web Serial bağlantısı ve firmware kaynakları içerir.

## Çalıştırma

```sh
git clone https://github.com/busrabuseucar/foodcycle.git
cd foodcycle
python3 -m http.server 5174 --directory web --bind 127.0.0.1
```

http://127.0.0.1:5174 adresini aç. Windows'ta `python3` yerine `python` kullanılabilir. API anahtarı veya backend gerekmez. İlk açılış boştur; “Jüri Demo Senaryosu” formu doldurur, “Ölçümü İşle” kaydeder.

Mevcut yayın adresi: https://foodcycle-ai-web-mvp.vercel.app — bu adresin güncel commit ile eşleşmesi ayrıca doğrulanmalıdır. Vercel Root Directory `web` olmalıdır; uygulama statiktir.

## Veri modeli ve hesaplar

- Her satır **ek bir atık tartımıdır**. Aynı tarih + öğün + kaynak tek yemek servisi kabul edilir. Aynı servis için kişi, üretim ve plan değerleri değiştirilemez. Birden çok lokasyon henüz desteklenmez.
- Kayıtlı atık / kişi = seçili kaynaktaki toplam gram / benzersiz servislerin toplam kişi sayısı. Ek tartımlar aynı insanları tekrar saymaz. Bu değer yalnızca girilmiş tartımları kapsar; eksik kategori girişi tüm atığın ölçüldüğü anlamına gelmez.
- Üretim fazlası % = toplam fazla gram / servislerin toplam üretim gramı × 100.
- Toplam plan-gerçek sapması % = |toplam plan − toplam gerçek| / toplam plan × 100. Servisler arası ters yönlü sapmalar birbirini götürebilir; MAE/MAPE değildir.
- Grafik seçili tarihle biten 7 **takvim gününü** gösterir. Veri olmayan gün `—` olur, sıfır varsayılmaz. KPI kartları seçili kaynağın tüm kayıtlarını kapsar.
- Demo/manuel ve fiziksel sensör verileri ayrı filtrelenir. Aynı tartımı tekrar kaydetmek çift sayım oluşturur; fiziksel yükün kimliğini otomatik tespit eden bir sistem yoktur.
- Tahmin ekranı %70 gerçek + %30 planlanan kişi kuralıdır. Üretim, mevcut kişi başı üretimle ölçeklenir. Eğitilmiş model, doğrulanmış talep tahmini veya otomatik azaltım değildir.
- Önce/sonra ekranı elle girilen değerlerin yüzde değişimidir; nedensel müdahale etkisi veya saha başarısı değildir.
- Önlenebilir/yönlendirilebilir atık, CO₂e ve ekonomik tasarruf ölçülmediği için üretilmez.

## Saklama ve sınırlar

Kayıtlar ve operatör notları yalnızca aynı tarayıcı/origin içinde `foodcycle.v1` altında tutulur. Site verilerini silmek veriyi siler. Bozuk kayıt üzerine otomatik yazılmaz; kota hatasında başarılı kayıt mesajı verilmez. Fark edilen başka sekme değişikliği engellenir; localStorage tam işlem/çok kullanıcılı veri bütünlüğü sağlamaz. Dışa aktarım, kayıt düzenleme ve tekil silme henüz yoktur. “Sıfırla” onayla tüm yerel kayıtları ve notları temizler.

Sunucu, kimlik doğrulama, REST API, PostgreSQL ve eğitilmiş AI modeli **uygulanmadı**. Arayüzdeki üretim mimarisi hedef tasarımdır. Gerçek hassas veri için uygun değildir.

## Sensör ve firmware

- Web Serial için uyumlu masaüstü tarayıcısı, HTTPS/localhost ve kullanıcı cihaz izni gerekir.
- 115200 baud, satır sonuyla ayrılmış JSON. `stable` boolean; ağırlık sonlu ve negatif olmayan sayı; cihaz ve kalibrasyon kimlikleri zorunlu.
- Yalnızca bağlı cihazdan son 5 saniyede alınmış pozitif, stabil örnek forma aktarılır. Kayıt sırasında da süre kontrol edilir. Değiştirilen ağırlık fiziksel ölçüm olarak kaydedilmez.
- Hatalı paket, cihaz olayı, kararsız örnek veya bağlantı kapanması aktarımı geçersiz kılar. Bir aktarım bir kez kaydedilir. Kalibrasyon kimliği kalibrasyon doğruluğunu tek başına kanıtlamaz.
- Ana sketch: `firmware/FoodCycleAI_ESP32_HX711/FoodCycleAI_ESP32_HX711.ino`.
- Kalibrasyon sketch: `firmware/FoodCycleAI_HX711_Calibration/FoodCycleAI_HX711_Calibration.ino`.
- İki sketch ayrı klasördedir; Arduino IDE'de ayrı açılır. `HX711` için **bogde** kütüphanesi hedeflenir. Kalibrasyon faktörü örnektir; referans ağırlıkla ayarlanmalıdır. Firmware gram çıktısı için `get_units` değerini kg kabul eder.
- İlk beş örnek dolmadan ve tare sonrası yeniden dolmadan stabil kabul edilmez.

Fiziksel donanım, firmware derlemesi ve kalibrasyon bu yazılım incelemesinde doğrulanmadı. [Bağlantı planı](docs/01_BAGLANTI_PLANI.md) ve [donanım test protokolü](docs/03_TEST_PROTOKOLU.md) sahada uygulanmalı.

## Testler

```sh
npm ci
npm test
```

Node.js 22/24 CI: hesaplama, günlük toplama, doğrulama, saklama hataları, yenileme, HTML enjeksiyonu ve sensör aktarımı kontrolleri. DOM testleri jsdom kullanır; gerçek tarayıcı veya fiziksel USB testi yerine geçmez.

[Teknik Tasarım ve Kararlar](docs/TECHNICAL_DESIGN.md)

Geliştirici: Büşra Buse Uçar · ATOM Labs

## İşletim

[İşletim ve sürüm doğrulama](docs/OPERATIONS.md) — kurulum, veri saklama, yayın, geri dönüş ve doğrulama kapsamı.
