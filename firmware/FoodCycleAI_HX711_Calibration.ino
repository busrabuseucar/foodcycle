/*
 FoodCycle AI - HX711 Calibration Utility
 1) Remove all weight from platform.
 2) Upload and open Serial Monitor @115200.
 3) Tare happens automatically.
 4) Place a known reference mass.
 5) Change calibration_factor using +/- commands until displayed weight matches reference.
 6) Copy final factor into FoodCycleAI_ESP32_HX711.ino
*/
#include "HX711.h"
#define DOUT 4
#define CLK 5
HX711 scale;
float calibration_factor = -7050.0;

void setup(){
  Serial.begin(115200);
  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare(20);
  Serial.println("FoodCycle AI Calibration");
  Serial.println("Known mass yerleştirin. +/- ile factor ayarlayın; T ile tare.");
}
void loop(){
  scale.set_scale(calibration_factor);
  Serial.print("Weight: ");
  Serial.print(scale.get_units(10)*1000.0, 1);
  Serial.print(" g | factor: ");
  Serial.println(calibration_factor);

  if(Serial.available()){
    char c=Serial.read();
    if(c=='+') calibration_factor += 10;
    if(c=='-') calibration_factor -= 10;
    if(c=='T'||c=='t') scale.tare(20);
  }
  delay(600);
}
