/*
  FoodCycle AI Physical MVP V1.0
  ESP32 + HX711 + Load Cell
  Serial JSON stream for Web Serial integration.

  Library:
    HX711 by bogde API: begin(), set_scale(), tare(), get_units()
*/

#include "HX711.h"

#define HX711_DOUT  4
#define HX711_SCK   5

HX711 scale;

// IMPORTANT: Replace after calibration.
float CALIBRATION_FACTOR = -7050.0f;

const char* DEVICE_UID = "FC-PILOT-01";
const char* CAL_VERSION = "CAL-001";

const int SAMPLE_COUNT = 8;
const float STABLE_THRESHOLD_G = 8.0f;
const unsigned long STREAM_INTERVAL_MS = 500;

float lastWeights[5] = {0,0,0,0,0};
int wIndex = 0;
int sampleWindowCount = 0;
unsigned long lastStream = 0;

float readWeightGrams() {
  float kg = scale.get_units(SAMPLE_COUNT);
  return kg * 1000.0f;
}

bool isStable(float current) {
  lastWeights[wIndex] = current;
  wIndex = (wIndex + 1) % 5;

  if(sampleWindowCount < 5) sampleWindowCount++;
  if(sampleWindowCount < 5) return false;
  float minV = lastWeights[0], maxV = lastWeights[0];
  for(int i=1;i<5;i++){
    if(lastWeights[i] < minV) minV = lastWeights[i];
    if(lastWeights[i] > maxV) maxV = lastWeights[i];
  }
  return (maxV - minV) <= STABLE_THRESHOLD_G;
}

void printJson(float weightG, bool stable){
  Serial.print("{\"device_uid\":\"");
  Serial.print(DEVICE_UID);
  Serial.print("\",\"weight_g\":");
  Serial.print(weightG, 1);
  Serial.print(",\"stable\":");
  Serial.print(stable ? "true" : "false");
  Serial.print(",\"calibration_version\":\"");
  Serial.print(CAL_VERSION);
  Serial.println("\"}");
}

void setup() {
  Serial.begin(115200);
  delay(500);

  scale.begin(HX711_DOUT, HX711_SCK);
  scale.set_scale(CALIBRATION_FACTOR);
  scale.tare(20);

  Serial.println("{\"event\":\"boot\",\"device_uid\":\"FC-PILOT-01\",\"status\":\"ready\"}");
}

void loop() {
  // Commands from Serial Monitor / future browser bridge:
  // T = tare
  if(Serial.available()){
    char c = Serial.read();
    if(c=='T' || c=='t'){
      scale.tare(20);
      sampleWindowCount = 0;
      Serial.println("{\"event\":\"tare\",\"status\":\"ok\"}");
    }
  }

  if(millis() - lastStream >= STREAM_INTERVAL_MS){
    lastStream = millis();

    if(scale.is_ready()){
      float weightG = readWeightGrams();
      if(weightG < 0 && weightG > -20) weightG = 0;
      bool stable = isStable(weightG);
      printJson(weightG, stable);
    }else{
      sampleWindowCount = 0;
      Serial.println("{\"event\":\"sensor_error\",\"code\":\"HX711_NOT_READY\"}");
    }
  }
}
