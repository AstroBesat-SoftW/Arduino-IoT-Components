<?php
// yourdomain.com/maps/kaydet.php

// ESP8266'dan gelen verileri al (GET metodu ile)
if(isset($_GET['lat']) && isset($_GET['lng'])) {
    
    $veriler = array(
        'enlem' => $_GET['lat'],
        'boylam' => $_GET['lng'],
        'rakim' => isset($_GET['alt']) ? $_GET['alt'] : '0',
        'saat' => isset($_GET['saat']) ? $_GET['saat'] : 'Bilinmiyor',
        'hiz' => isset($_GET['hiz']) ? $_GET['hiz'] : '0',
        'son_guncelleme' => date('Y-m-d H:i:s')
    );

    // Verileri JSON formatına çevir ve dosyaya yaz
    file_put_contents('konum.json', json_encode($veriler));
    
    echo "Veri Kaydedildi";
} else {
    echo "HATA: Enlem ve boylam verisi eksik!";
}
?>