#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(
  U8G2_R0,        
  U8X8_PIN_NONE   
);

void setup() {
  // Mulai OLED
  u8g2.begin();

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB14_tr);   // pilih font
  u8g2.drawStr(0, 20, "Hello Aldi");
  u8g2.drawStr(0, 40, "ESP32-C3");
  u8g2.sendBuffer();
}

void loop() {
  // kosong dulu, karena teksnya statis
}
