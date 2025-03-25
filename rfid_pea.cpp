#include "pea.h"

volatile uint64_t wiegandData = 0;
volatile int bitCount = 0;
volatile unsigned long lastPulseTime = 0;

void D0Interrupt() {
  wiegandData = (wiegandData << 1);
  bitCount++;
  lastPulseTime = millis();
}

void D1Interrupt() {
  wiegandData = (wiegandData << 1) | 1;
  bitCount++;
  lastPulseTime = millis();
}

void decodeWiegand(uint64_t data, int bitCount) {
  if(bitCount != 44) {
    Serial.println("Erreur : le nombre de bits reçus n'est pas égal à 44.");
    return;
  }
  
  uint64_t cardData = data >> 4;
  uint8_t xorValue = data & 0xF;
  uint8_t calculatedXor = 0;
 
  for (int i = 0; i < 10; i++) {
    uint8_t nibble = (cardData >> ((9 - i) * 4)) & 0xF;
    calculatedXor ^= nibble;
  }

  Serial.print("Card Data: 0x");
  for (int i = 9; i >= 0; i--) {
    uint8_t nibble = (cardData >> (i * 4)) & 0xF;
    if(nibble < 10)
      Serial.print(nibble);
    else
      Serial.print((char)('A' + nibble - 10));
  }
  
  if(calculatedXor == xorValue) {
    Serial.println(" + Checksum valide.");
  } else {
    Serial.println("Checksum invalide !");
  }
}

void printRawWiegandBits() {
  Serial.print("Trame brute reçue (");
  Serial.print(bitCount);
  Serial.println(" bits):");
  
  for (int i = bitCount - 1; i >= 0; i--) {
    Serial.print((wiegandData >> i) & 1);
  }
  Serial.println();
  
  wiegandData = 0;
  bitCount = 0;
}
