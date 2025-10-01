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

// // Hook up HC-SR04 
#define TRIGGER_PIN 9 // Trig to Arudino pin 9,
#define ECHO_PIN 10 //  Echo to Arduino pin 10
#define MAX_DISTANCE 400 //

// pinMode(TRIGGER_PIN, OUTPUT);
// pinMode(ECHO_PIN, INPUT);

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

void setup() {
  // put your setup code here, to run once:

  //Initialize Serial Monitor
  Serial.begin(9600); // begin communicating at 9600 bits per second
  dht.begin(); // intialize temp and humidity sensor

}

void loop() {


// sketch version 2 - more accurate!

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
  Serial.println(" cm");
  delay(500);
}
delay(500);


}
