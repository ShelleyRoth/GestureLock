
// Inlcude EEPROM to store the password so that is survives power cycles on the Arduino
#include <EEPROM.h>

// Include the struct definition of a password digit (gesture + distance)
#include "Password.h"

// ******CONSTANTS******
#define MAX_PASSWORD_LENGTH 4  // The maximum length of the password

#define INT_GESTURE_THUMBS_UP 1
#define INT_GESTURE_FIST 2
#define INT_GESTURE_OPEN_HAND 3

#define PASSWORD_ADDRESS 0


// example password pair of hand gesture + distance
// { (gesture=1, distance=2), (gesture=0, distance=1), (gesture=3, distance=0), (gesture=2, distance=2) }


// ******Variables******

int digitIndex = 0;


// Password-related variables
int storedLength = 0;
int storedUserPasscode[MAX_PASSWORD_LENGTH][2];  // [i][0]=gestureID, [i][1]=distanceZone
bool hasPassword = false;

PasswordDigit correctPassword[MAX_PASSWORD_LENGTH] = { {1, 2}, {0, 1}, {2, 0}, {3, 2} }; // temperary password just for testing
PasswordDigit attemptedPassword[MAX_PASSWORD_LENGTH] = {};


bool checkPasswordMatch(int attemptLength, PasswordDigit* attemptPassword, PasswordDigit* correctPassword) {
  if(attemptLength != MAX_PASSWORD_LENGTH) {
    return false;
  }

  for(int i = 0; i < MAX_PASSWORD_LENGTH; i++) { // navigate through the whole password
    if(attemptPassword[i].gesture != correctPassword[i].gesture || attemptPassword[i].distance != correctPassword[i].distance) {
      Serial.println("Wrong password");
      return false;
    }
  }
  Serial.println("Unlocked!");
  return true;

}

void loadPasswordFromEEPROM(PasswordDigit* passwordCombination, int length) {
  int address = PASSWORD_ADDRESS;
  for (int i = 0; i < MAX_PASSWORD_LENGTH; i++) {
    passwordCombination[i].gesture = EEPROM.read(address++);
    passwordCombination[i].distance = EEPROM.read(address++);
  }
}

void savePasswordToEEPROM(PasswordDigit* passwordCombination, int length) {
  int address = PASSWORD_ADDRESS;
  for (int i = 0; i < length; i++) {
    EEPROM.write(address++, passwordCombination[i].gesture);
    EEPROM.write(address++, passwordCombination[i].distance);
  }
}
