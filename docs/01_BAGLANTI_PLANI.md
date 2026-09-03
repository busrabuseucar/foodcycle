# FoodCycle AI — Fiziksel MVP Bağlantı Planı

## Temel BOM
- ESP32 DevKit V1 — 1 adet
- HX711 load cell amplifier — 1 adet
- Load Cell (öneri: 20–50 kg, prototip platformuna göre) — 1 adet / set
- Stabil tartım platformu
- USB data kablosu
- Jumper kablo / lehim bağlantıları
- Referans kalibrasyon ağırlığı (bilinen kütle)

## ESP32 ↔ HX711
| HX711 | ESP32 |
|---|---|
| VCC | 3V3 |
| GND | GND |
| DT / DOUT | GPIO 4 |
| SCK / CLK | GPIO 5 |

## Load Cell ↔ HX711
Load cell kablo renkleri üreticiye göre değişebilir. Kart üzerindeki E+, E-, A+, A- işaretlerine göre sensör datasheet'ini izleyin; yalnızca renk üzerinden bağlantı yapmayın.

## Veri zinciri
Load Cell → HX711 → ESP32 → USB Serial JSON → Chrome/Edge Web Serial → FoodCycle AI Web MVP

Bu prototipte backend zorunlu değildir. Web Serial kullanımı, fiziksel sensör verisini tarayıcıdaki çalışan MVP'ye en kısa ve en düşük riskli yoldan bağlar.
