# FoodCycle AI

**Akıllı Atık Azaltımı ve Döngüsel Ekonomi Karar Destek Sistemi**  
ATOM Labs · TEKNOFEST 2026 · Sıfır Atık & Döngüsel Ekonomi

> Atığı saymak yerine, nedenini öğrenen ve bir sonraki kararı değiştiren sistem.

## Proje özeti
FoodCycle AI; toplu yemek operasyonlarında gıda atığını yalnızca ölçmekle kalmayıp ölçüm → doğrulama → KPI → tahmin → müdahale → yeniden ölçüm döngüsüne taşıyan karar destek sistemidir.

Canlı Web MVP: https://foodcycle-ai-web-mvp.vercel.app

## Çalışan Web MVP
- Simüle sensörlü atık kaydı
- KPI dashboard
- 7 günlük kişi başı atık trendi
- Açıklanabilir demo tahmin akışı
- Intervention Engine
- Operatör müdahale kaydı
- Baseline / müdahale sonrası etki hesabı
- Olay kayıtları / izlenebilirlik

## Fiziksel MVP mimarisi
`Load Cell → HX711 → ESP32 → USB Serial JSON → Web Serial → FoodCycle AI Web MVP`

Hedef üretim mimarisi:
`Load Cell → HX711 → ESP32 → REST/JSON → PostgreSQL → Analytics / Prediction / Intervention → Dashboard`

## Teknolojiler
HTML5, CSS3, JavaScript, Vercel, ESP32, HX711, Load Cell, Web Serial, REST/JSON, PostgreSQL, HTTPS/TLS, Git.

## Repo yapısı
- `web/index.html` — Web Serial destekli Web MVP V2.1
- `firmware/FoodCycleAI_ESP32_HX711.ino` — ana ESP32 firmware
- `firmware/FoodCycleAI_HX711_Calibration.ino` — HX711/load cell kalibrasyon aracı
- `docs/` — bağlantı, JSON protokolü, test protokolü ve 72 saatlik fiziksel MVP planı

## Doğruluk sınırı
Bu repodaki Web MVP simüle sensör verisiyle de çalışabilir. Fiziksel sensör gerçekten bağlanıp kalibre edilene kadar saha validasyonu, doğrulanmış atık azaltım oranı veya gerçek pilot başarısı iddia edilmez. CO₂e ve ekonomik etki yalnızca doğrulanmış katsayılarla hesaplanacaktır.

## Takım
ATOM Labs — TEKNOFEST 2026
