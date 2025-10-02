#ifndef PASSWORD_H
#define PASSWORD_H

#include <Arduino.h>   // for byte type
#include <EEPROM.h>    // for EEPROM functions

#define MAX_PASSWORD_LENGTH 4
#define PASSWORD_ADDRESS 0

struct PasswordDigit {
  byte gesture;
  byte distance;
};

void savePasswordToEEPROM(PasswordDigit* passwordCombination, int length);
void loadPasswordFromEEPROM(PasswordDigit* passwordCombination, int length)

#endif
