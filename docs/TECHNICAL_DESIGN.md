# Teknik Tasarım ve Kararlar

## Veri modeli
FoodCycle, atık tartımlarını yemek servisi bağlamıyla kaydeden bir yerel prototip. Bir öğünde birden fazla tartım yapılabildiği için kişi ve üretim bilgilerini her tartımda toplamak hatalı olur. Servis kimliğini tarih/öğün/kaynak olarak gruplayarak normalize hesap yapar. Çok lokasyonlu kullanımda servis kimliği ve lokasyon alanı eklenmeli.

## Tasarım kararları
- Hesaplar kayıt verisinden türetiliyor; başlangıçta uydurma KPI ve trend yok.
- Veri olmayan gün ile gerçekten sıfır atık ölçülen gün farklıdır. Bu sürüm yalnızca pozitif tartım kabul ettiğinden kayıt yokluğu sıfır sayılmaz.
- Sensör güvenilirliği yalnızca `stable` alanıyla belirlenmez. Bağlantı durumu, paket şeması, alınma zamanı ve kaynağın saklanması da kontrol edilir. Fiziksel kalibrasyon ayrıca gerekir.
- Notlar ve cihaz alanları textContent ile gösterilir; HTML olarak çalıştırılmaz.
- Kalıcı saklama başarısızsa uygulama belleği başarılı kayıt varmış gibi ilerlemez.
- Tahmin ağırlıkları ve müdahale eşikleri demo kurallarıdır. Eğitim, karşılaştırmalı değerlendirme ve saha verisi olmadan AI doğruluğu iddiası yoktur.

## Sonraki gerçek ürün adımları
Servis/lokasyon kimlikleri, kayıt düzeltme ve dışa aktarım; sunucu tarafı doğrulama ve rol denetimi; kalibrasyon kayıtları; referans kütlelerle hata ölçümü; karşılaştırılabilir servislerde baseline değerlendirmesi. Önce/sonra aritmetiği tek başına müdahalenin işe yaradığını kanıtlamaz.
