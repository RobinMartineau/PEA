#ifndef PEA_H
#define PEA_H

#include <Arduino.h>
#include <stdint.h>

extern volatile uint64_t wiegandData;
extern volatile int bitCount;
extern volatile unsigned long lastPulseTime;

#define D0_PIN PA2
#define D1_PIN PA3
#define WIEGAND_TIMEOUT 50
#define RELAY_PIN PA8

void D0Interrupt();
void D1Interrupt();
void decodeWiegand(uint64_t data, int bitCount);
void printRawWiegandBits();

#endif
