# FoodCycle AI

**Akıllı Atık Azaltımı ve Döngüsel Ekonomi Karar Destek Sistemi**  
ATOM Labs · TEKNOFEST 2026 · Sıfır Atık & Döngüsel Ekonomi

> Atığı saymak yerine, nedenini öğrenen ve bir sonraki kararı değiştiren sistem.

## Canlı sürüm
**Final Web MVP V2.1**

Canlı Web MVP: https://foodcycle-ai-web-mvp.vercel.app

V2.1; simüle demo akışına ek olarak ESP32 + HX711 + Load Cell fiziksel ölçüm zincirinin masaüstü Chrome/Edge üzerinden Web Serial ile bağlanmasına hazırdır. Fiziksel sensör bağlanıp kalibre edilmeden gerçek saha/pilot başarısı iddia edilmez.

## Çalışan Web MVP
- Simüle sensörlü atık kaydı
- KPI dashboard
- 7 günlük kişi başı atık trendi
- Açıklanabilir demo tahmin akışı
- Intervention Engine
- Operatör müdahale kaydı
- Baseline / müdahale sonrası etki hesabı
- Olay kayıtları / izlenebilirlik
- Web Serial fiziksel sensör bağlantı arayüzü
- Stabil sensör ölçümünü forma aktarma akışı

## Fiziksel MVP mimarisi
`Load Cell → HX711 → ESP32 → USB Serial JSON → Web Serial → FoodCycle AI Web MVP V2.1`

Hedef üretim mimarisi:
`Load Cell → HX711 → ESP32 → REST/JSON → PostgreSQL → Analytics / Prediction / Intervention → Dashboard`

## Teknolojiler
HTML5, CSS3, JavaScript, Vercel, ESP32, HX711, Load Cell, Web Serial, REST/JSON, PostgreSQL, HTTPS/TLS, Git/GitHub.

## Repo yapısı
- `web/index.html` — Web Serial destekli Final Web MVP V2.1
- `firmware/FoodCycleAI_ESP32_HX711.ino` — ana ESP32 firmware
- `firmware/FoodCycleAI_HX711_Calibration.ino` — HX711/load cell kalibrasyon aracı
- `docs/` — bağlantı, JSON protokolü, test protokolü ve 72 saatlik fiziksel MVP planı

## V2.1 sensör veri sözleşmesi
ESP32, 115200 baud üzerinden satır bazlı JSON üretir:

```json
{"device_uid":"FC-PILOT-01","weight_g":1850,"stable":true,"calibration_version":"CAL-001"}
```

Web arayüzü yalnızca `stable=true` olan son fiziksel ölçümün forma aktarılmasına izin verir.

## Doğruluk sınırı
Web MVP demo verisiyle çalışabilir. ESP32, HX711 ve Load Cell fiziksel olarak bağlanıp kalibre edilerek test protokolü tamamlanana kadar saha validasyonu, doğrulanmış atık azaltım oranı veya gerçek pilot başarısı iddia edilmez. CO₂e ve ekonomik etki yalnızca doğrulanmış katsayılarla hesaplanacaktır.

## Takım
ATOM Labs — TEKNOFEST 2026
