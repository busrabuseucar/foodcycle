# FoodCycle AI — Fiziksel MVP Test Protokolü

## A. Elektrik / haberleşme
- [ ] ESP32 USB ile açılıyor
- [ ] HX711 ready durumu geliyor
- [ ] Serial Monitor 115200 baud JSON satırları gösteriyor
- [ ] Sensör yük altında anlamlı değişim gösteriyor

## B. Kalibrasyon
- [ ] Boş platform tare = yaklaşık 0 g
- [ ] En az 3 referans ağırlıkla test
- [ ] Her referansta mutlak hata kaydedildi
- [ ] Kalibrasyon faktörü ve tarihi sürümlendi

## C. Stabilite
- [ ] Yük sabitken stable=true
- [ ] Platform hareket ettirilirken stable=false
- [ ] 10 tekrar ölçümde saçılım kaydedildi

## D. Web entegrasyonu
- [ ] Chrome/Edge üzerinden ESP32 seçildi
- [ ] Son sensör ağırlığı ekranda göründü
- [ ] Fiziksel ölçüm forma aktarıldı
- [ ] Ölçümü İşle sonrası KPI değişti
- [ ] Intervention Engine senaryosu çalıştı
- [ ] Baseline/post doğrulama çalıştı

## E. Jüri demo kabul kriteri
1. Referans ağırlığı platforma koy.
2. Web MVP'de sensör değeri canlı görünsün.
3. Değeri forma aktar.
4. Ölçümü işle.
5. KPI ve trend değişsin.
6. Müdahale önerisi oluşsun.
7. Operatör müdahaleyi kaydetsin.
8. Önce/sonra etki ekranı gösterilsin.

Bu sekiz adım kesintisiz yapılabiliyorsa fiziksel uçtan uca demo kabul edilir.
