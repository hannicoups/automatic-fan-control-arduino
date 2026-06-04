#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ======================
// KONFIGURASI PIN
// ======================

#define DHTPIN 5
#define DHTTYPE DHT11

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

const int jumlahData = 10;
const int batasSuhu = 25;
const int batasCahaya = 500;

void setup() {

  Serial.begin(9600);

  dht.begin();

  lcd.init();
  lcd.backlight();

  pinMode(RELAY_PIN, OUTPUT);

  // Relay OFF saat awal
  digitalWrite(RELAY_PIN, LOW);

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
  // AMBIL 10 DATA SUHU
  // ======================

  for (int i = 0; i < jumlahData; i++) {

    float suhu = dht.readTemperature();

    if (!isnan(suhu)) {

      totalSuhu += suhu;

      // SERIAL MONITOR
      Serial.print("Suhu ke-");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.println(suhu);

      // LCD REALTIME
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("T");
      lcd.print(i + 1);
      lcd.print(":");
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
      i--;
    }

    delay(2000); 
  }

  // ======================
  // HITUNG RATA-RATA
  // ======================

  rataSuhu = totalSuhu / jumlahData;

  // ======================
  // BACA LDR
  // ======================

  int nilaiLDR = analogRead(LDR_PIN);

  String kondisiCahaya;

  if (nilaiLDR < batasCahaya) {
    kondisiCahaya = "TERANG";
  } else {
    kondisiCahaya = "GELAP";
  }

  // ======================
  // KEPUTUSAN FAN BERDASARKAN RATA-RATA
  // ======================

  bool fanNyala = (rataSuhu >= batasSuhu);

  if (fanNyala) {
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    digitalWrite(RELAY_PIN, LOW);
  }

  // ======================
  // LCD HASIL AKHIR
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
    lcd.print("FAN OFF");
  }

  lcd.print(" ");
  lcd.print(kondisiCahaya);

  // ======================
  // SERIAL MONITOR AKHIR
  // ======================

  Serial.println();

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

  delay(5000);
}


