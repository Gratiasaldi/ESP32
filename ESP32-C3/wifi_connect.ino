#include <WiFi.h>

const char* ssid     = "NAMA_WIFI";
const char* password = "PASSWORD_WIFI";

unsigned long lastCheck = 0;
const unsigned long checkInterval = 5000; 

void connectWiFi() {
  Serial.println();
  Serial.print("Menghubungkan ke: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int retry = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    retry++;
    if (retry > 40) {
      Serial.println();
      Serial.println("Gagal connect, cek SSID / password / jarak router.");
      return;
    }
  }

  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  connectWiFi();
}

void loop() {
  unsigned long now = millis();

  // Cek koneksi berkala
  if (now - lastCheck >= checkInterval) {
    lastCheck = now;

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi terputus, mencoba reconnect...");
      connectWiFi();
    }
  }

  // logic utama programmu di sini
}
