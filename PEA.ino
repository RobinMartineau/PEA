#include "pea.h"

void deverrouillerGache() {
  Serial.println("Déverrouillage de la gâche...");
  digitalWrite(RELAY_PIN, HIGH);
  delay(10000);
  digitalWrite(RELAY_PIN, LOW);
  Serial.println("Gâche verrouillée.");
}


void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(D0_PIN, INPUT_PULLUP);
  pinMode(D1_PIN, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(D0_PIN), D0Interrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(D1_PIN), D1Interrupt, FALLING);
  
  Serial.println("Lecture brute Wiegand en cours...");
}

void loop() {
if(bitCount == 44) {
  decodeWiegand(wiegandData, bitCount);
  printRawWiegandBits();
  deverrouillerGache();
}
}
