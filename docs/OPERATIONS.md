# İşletim ve sürüm doğrulama — Atık tartımı ve kural tabanlı karar desteği

Son inceleme: **16 Ekim 2026**. Bu belge kurulum, veri akışı, sürüm kapıları, geri dönüş ve doğrulama kapsamını birlikte kaydeder. Bir yayın adresinin açılması, tüm üretim koşullarının tamamlandığı anlamına gelmez.

## Sürüm kanıtı

- Denetlenen uygulama commit’i: `54eb3e40e274f79c5173bc162093c91ca25a1a32`.
- [Bu commit için başarılı CI kaydı](https://github.com/busrabuseucar/foodcycle/actions/runs/38898592952).
- Doğrulanan otomatik kapsam: 12 DOM/hesap/sensör aktarımı testi; iki ESP32 firmware hedefi için başarılı derleme (ayrıntılar: [firmware kaydı](FIRMWARE_BUILD.md)).
- Testlerin gerçek servis, veri veya donanım yerine taklit kullandığı noktalar aşağıda açıkça ayrılmıştır.

## Kurulum ve çalışma

Depo kökünde, README’deki çalışma zamanı sürümüyle:

```sh
npm ci
npm test
python3 -m http.server 5174 --directory web --bind 127.0.0.1
```

Veri akışı: Manuel veya seri port ölçümü → stabil/taze paket kontrolü → servis bazlı hesap → localStorage.

Yapılandırma: Vercel Root Directory web; statik çıktı. ESP32/HX711, 115200 baud ve gram protokolü. Her fiziksel cihaz için gerçek kalibrasyon gerekir.

## Yayın ve geri dönüş

1. Temiz checkout ve kilitli bağımlılıklarla yukarıdaki kontrolleri çalıştır. İlgili CI başarısını commit SHA ile eşleştir.
2. Yayın paketine yalnızca çalışma zamanı dosyalarını koy. Secret, ham kullanıcı verisi, yerel veritabanı ve kişisel hazırlık notları pakete girmemeli.
3. Hedef proje, kaynak commit, ortam ve yayın sürümünü kaydet. Önceki çalışan sürüm kimliğini geri dönüş için koru.
4. Yayından sonra ana kullanıcı akışını, hata durumunu ve varsa kalıcılığı doğrula. Sunucu hatası/yanlış sonuçta yeni yazmaları durdur; önceki doğrulanmış yayını geri al.
5. Şema değiştiyse yalnızca kodu geri almak yeterli değildir. Yedekten ayrı ortamda doğrulama yapmadan canlı veri üzerine yazma.

## Veri saklama ve kurtarma

foodcycle.v1 yalnızca aynı tarayıcı origin’inde. Yerel veri dışa aktarımı/geri yükleme henüz yok; üretim kayıt sistemi değildir. Sıfırla işlemi bütün yerel veriyi siler.

## Gerçek servis, model ve cihaz doğrulaması

Fiziksel ESP32/HX711, referans ağırlıklar, USB bağlantı/kopma, tare, drift ve tekrarlanabilirlik testi bu ortamdan yapılamaz. docs/03_TEST_PROTOKOLU.md uygulanmalı. Model yok: %70 gerçek/%30 plan kuralı kullanılır.

## Yayın sonrası gözlem

Önce küçük ve sentetik girdilerle temel akışı kontrol et. Beklenmeyen hata, boş ekran, yanlış hesap, yetkisiz erişim veya veri kaybında tarih, uygulama commit’i, ortam ve yeniden üretme adımlarını kaydet; kişisel veri ve secret ekleme. Statik araçlarda tarayıcı konsolu/ağ hatalarını; backend bulunan projelerde durum kodu, gecikme ve hata oranını incele. Bu belgede sürekli izleme veya otomatik geri dönüş kurulmuş olduğu iddia edilmez.

## Kabul kaydı

Her yeni sürümün kaydı; test komutu/sonucu, kaynak SHA, yayın sürümü, gerçek servis/model sürümü, cihaz/işletim sistemi, veri kümesi özeti ve geri dönüş denemesini içermeli. Erişim veya fiziksel donanım yoksa ilgili satır **çalıştırılmadı** olarak tutulur; otomatik test başarısı yerine geçirilmez.
