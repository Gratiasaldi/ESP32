// ====== Konfigurasi Pin ======
const int BUTTON_PIN = 2;   

// ====== Konfigurasi Waktu ======
const unsigned long DEBOUNCE_DELAY   = 50;    
const unsigned long LONG_PRESS_TIME  = 1000;  
const unsigned long MIN_PRESS_TIME   = 50;    

// ====== Variabel internal ======
int buttonState      = HIGH;  
int lastReading      = HIGH;  

unsigned long lastDebounceTime = 0;
unsigned long pressedTime      = 0;
unsigned long releasedTime     = 0;

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(BUTTON_PIN, INPUT_PULLUP);   

  Serial.println("=== ESP32-C3 Button Test ===");
  Serial.println("Short press vs Long press");
  Serial.println("Tekan tombol untuk mulai...");
}

void loop() {
  int reading = digitalRead(BUTTON_PIN);

  // Cek perubahan (untuk debounce)
  if (reading != lastReading) {
    lastDebounceTime = millis();
    lastReading = reading;
  }

  // Kalau sudah stabil lebih dari DEBOUNCE_DELAY
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    // Kalau ada perubahan status stabil
    if (reading != buttonState) {
      buttonState = reading;

      // TRANSISI: TINGGI -> RENDAH = tombol baru ditekan
      if (buttonState == LOW) {
        pressedTime = millis();
        // Kalau mau debug:
        // Serial.println("BUTTON DOWN");
      }

      // TRANSISI: RENDAH -> TINGGI = tombol baru dilepas
      else { // buttonState == HIGH
        releasedTime = millis();
        unsigned long pressDuration = releasedTime - pressedTime;

        // Filter noise: tekan terlalu singkat diabaikan
        if (pressDuration < MIN_PRESS_TIME) {
          // Serial.println("Noise / glitch detected");
          return;
        }

        if (pressDuration < LONG_PRESS_TIME) {
          Serial.print("Short press: ");
          Serial.print(pressDuration);
          Serial.println(" ms");
        } else {
          Serial.print("Long press : ");
          Serial.print(pressDuration);
          Serial.println(" ms");
        }
      }
    }
  }

}
