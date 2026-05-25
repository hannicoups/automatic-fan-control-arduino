#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ======================
// KONFIGURASI PIN
// ======================

#define DHTPIN 2
#define DHTTYPE DHT11      // Wokwi pakai DHT22

#define LDR_PIN A0
#define RELAY_PIN 8

// ======================
// INISIALISASI
// ======================

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

// ======================
// VARIABEL
// ======================

float totalSuhu = 0;
float rataSuhu = 0;

// jumlah pembacaan suhu
const int jumlahData = 10;

// batas suhu fan aktif
const int batasSuhu = 30; 

// batas cahaya LDR
const int batasCahaya = 500;

void setup() {

  Serial.begin(9600);

  // mulai sensor DHT
  dht.begin();

  // mulai LCD
  lcd.init();
  lcd.backlight();

  // relay sebagai output
  pinMode(RELAY_PIN, OUTPUT);

  // relay OFF awal
  // relay module active LOW
  digitalWrite(RELAY_PIN, HIGH);

  // tampilan awal LCD
  lcd.setCursor(0, 0);
  lcd.print("Automatic Fan");

  lcd.setCursor(0, 1);
  lcd.print("System Ready");

  delay(2000);

  lcd.clear();
}

void loop() {

  totalSuhu = 0;

  // ======================
  // PEMBACAAN SUHU REALTIME
  // ======================

  for (int i = 0; i < jumlahData; i++) {

    float suhu = dht.readTemperature();

    if (!isnan(suhu)) {

      // jumlahkan suhu
      totalSuhu += suhu;

      // rata-rata sementara
      rataSuhu = totalSuhu / (i + 1);

      // tampil serial monitor
      Serial.print("Suhu ke-");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.println(suhu);

      // ======================
      // FAN REALTIME
      // ======================

      // jika suhu realtime >= 30
      // fan langsung nyala sementara

      if (suhu >= batasSuhu) {

        // relay ON
        digitalWrite(RELAY_PIN, LOW);

      } else {

        // relay OFF
        digitalWrite(RELAY_PIN, HIGH);
      }

      // ======================
      // LCD REALTIME
      // ======================

      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Temp:");
      lcd.print(suhu);
      lcd.print((char)223);
      lcd.print("C");

      lcd.setCursor(0, 1);

      if (suhu >= batasSuhu) {

        lcd.print("FAN ON");

      } else {

        lcd.print("FAN OFF");
      }

    } else {

      Serial.println("Gagal baca DHT");

      // ulang pembacaan jika gagal
      i--;
    }

    delay(5000);
  }

  // ======================
  // HITUNG RATA-RATA FINAL
  // ======================

  rataSuhu = totalSuhu / jumlahData;

  // ======================
  // BACA SENSOR LDR
  // ======================

  int nilaiLDR = analogRead(LDR_PIN);

  String kondisiCahaya;

  if (nilaiLDR < batasCahaya) {

    kondisiCahaya = "TERANG";

  } else {

    kondisiCahaya = "GELAP";
  }

  // ======================
  // KEPUTUSAN FINAL FAN
  // ======================

  // fan aktif jika rata-rata suhu >= 30

  bool fanNyala = (rataSuhu >= batasSuhu);

  if (fanNyala) {

    // relay ON
    digitalWrite(RELAY_PIN, LOW);

  } else {

    // relay OFF
    digitalWrite(RELAY_PIN, HIGH);
  }

  // ======================
  // LCD FINAL
  // ======================

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Avg:");
  lcd.print(rataSuhu);
  lcd.print((char)223);
  lcd.print("C");

  lcd.setCursor(0, 1);

  if (fanNyala) {

    lcd.print("FAN ON ");

  } else {

    lcd.print("FAN OFF ");
  }

  lcd.print(kondisiCahaya);

  // ======================
  // SERIAL MONITOR FINAL
  // ======================

  Serial.print("Rata-rata Suhu: ");
  Serial.println(rataSuhu);

  Serial.print("Nilai LDR: ");
  Serial.println(nilaiLDR);

  Serial.print("Kondisi Cahaya: ");
  Serial.println(kondisiCahaya);

  if (fanNyala) {

    Serial.println("FAN ON");

  } else {

    Serial.println("FAN OFF");
  }

  Serial.println("====================");

  delay(2000);
}