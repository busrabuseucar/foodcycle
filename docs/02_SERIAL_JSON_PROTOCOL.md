# FoodCycle AI — Sensör JSON Sözleşmesi

ESP32 her 500 ms'de bir satır sonu ile JSON gönderir:

```json
{"device_uid":"FC-PILOT-01","weight_g":1850.0,"stable":true,"calibration_version":"CAL-001"}
```

Alanlar:
- `device_uid`: benzersiz istasyon/cihaz kimliği
- `weight_g`: net tartım değeri, gram
- `stable`: son örneklerin salınımı eşik altında ise true
- `calibration_version`: kullanılan kalibrasyon kaydının sürümü

Web MVP yalnızca `stable=true` olan son ölçümü operatörün forma aktarmasına izin verir.

## Tare komutu
USB Serial üzerinden `T` karakteri gönderildiğinde ESP32 platformu yeniden sıfırlar.
