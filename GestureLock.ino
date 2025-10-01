// Use the serial monitor to display the distance readings from the HC-SR04

// *******LIBRARIES*******

// Include the DHT Library from AdaFruit
// The library is dependent on AdaFruit_Sensors Library
#include "DHT.h" 

// Include NewPing Library by Tim Eckel
#include "NewPing.h"

// *******Constants*******

// Hook up DHT-11
#define DHT_PIN 7 // DHT-11 Output Pin connection
#define DHT_TYPE DHT11 // DHT type is DHT-11

// Hook up HC-SR04 
#define TRIGGER_PIN 9 // Trig to Arudino pin 9,
#define ECHO_PIN 10 //  Echo to Arduino pin 10
#define MAX_DISTANCE 400 //

// Thresholds for Distance Definitions
#define NEAR 10 // An object's distance x will be defined as near if x <= 10 cm
#define MEDIUM 20 // An object's distance x will be defined as medium if 10 < x <= 20
// An object's distance x will be defined as far if x > 20

// Integer defintion of NEAR, MEDIUM, and FAR
#define INT_NEAR 0
#define INT_MEDIUM 1
#define INT_FAR 2

// Button
#define BUTTON_PIN 2 // digital pin connected to the button

// Initialize DHT sensor
DHT dht(DHT_PIN, DHT_TYPE);

// Intialize NewPing
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// *******VARIABLES*******

float humidity; // Stores humidity value in percent
float temp; // Stores temperature value in Celcius
float duration; // Stores HC-SR04 pulse duration value
float distance; // Stores Calculated distance
float speedOfSoundMpS; // Stores calculated speed of sound in meters per second
float speedOfSoundCMpMS; // Stores calculated speed of sound in cm per microsecond
int iterations = 5; // to calculate average duration from a given object and stabalize output readings

int correctPasscode[3] = {0, 1, 2};
int userPasscode[3] = {};

void setup() {
  // put your setup code here, to run once:

  //Initialize Serial Monitor
  Serial.begin(9600); // begin communicating at 9600 bits per second
  dht.begin(); // intialize temp and humidity sensor
  pinMode(BUTTON_PIN, INPUT);

}

float calculateDistance() {

delay(2000); // delay so DHT sensor has time to stabalize

humidity = dht.readHumidity(); // get humidity value
temp = dht.readTemperature(); // get temperature value

// *******Calculations*******

// Calculate the speed of sound in meters per second
speedOfSoundMpS = 331 + 0.61 * temp + 0.0124 * humidity;

// Convert units of speed of sound from m/s to cm/s
speedOfSoundCMpMS = speedOfSoundMpS / 10000;

// record duration from HC-SR04 sensor to given object
duration = sonar.ping_median(iterations); // to get the average duration

//calculate distance
distance = speedOfSoundCMpMS * (duration / 2); // divide duration by 2 because the duration is calculated as a "round trip"


// Print details of speed of sound in m/s, humidity percentage, temperature in Celcius, and distance in cm
Serial.print("Sound: ");
Serial.print(speedOfSoundMpS);
Serial.print(" m/s, "); 
Serial.print("Humid: ");
Serial.print(humidity);
Serial.print("%, Temp: ");
Serial.print(temp);
Serial.print(" C, "); 
Serial.print("Distance: ");

// Send results to serial monitor
Serial.print("Distance = "); 
if(distance >= 400 || distance <= 2) {
  Serial.println("OUT OF RANGE");
} else {
  Serial.print(distance);
  Serial.print(" cm");
  if(distance <= NEAR) {
    Serial.println("NEAR");
  } else if(distance <= MEDIUM) {
    Serial.println("Medium");
  } else {
    Serial.println("FAR");
  }
  delay(500);
}
delay(500);

return distance;
}

bool isButtonPressed() {
  int buttonState = digitalRead(BUTTON_PIN);
  // check if button is pressed
  if(buttonState == LOW) {
    // debounce delay
    delay(50);
    //reread to confirm press after debounce
    if(digitalRead(BUTTON_PIN) == LOW) {
      // digitalWrite(LED_PIN, HIGH); // Turn LED on
      Serial.println("Button not Pressed");
    }
  } else {
    // digitalWrite(LED_PIN, LOW); // turn LED off
    Serial.println("Button Pressed");
  }
}


void loop() {
  int distance = calculateDistance();
  isButtonPressed();




}
