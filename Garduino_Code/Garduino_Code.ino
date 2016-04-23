/*
  Garduino Code V01
  Tested with Arduino Uno
  Ardunio IDE 1.6.6
*/
 
#include "DHT.h"
#include <Servo.h>

//Festlegen der Pinbelegung
#define DHTPIN 2 //Pinbelegung für DHT11 Sensor
#define DHTTYPE DHT11
const int pin_humidity_sensor = A0;

//Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

//Variablen
int humidity_soil = 0;
int humidity_soil_raw = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(19200);
  Serial.println("Serial Monitor online");
  dht.begin();
  pinMode(9, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // HUMIDITY SOIL: read the input on analog pin 0:
  humidity_soil_raw = analogRead(pin_humidity_sensor);
  humidity_soil = map(humidity_soil_raw, 0, 600, 0, 100);
  humidity_soil = constrain(humidity_soil, 0, 100);
  int sensorValue = map(humidity_soil, 0, 100, 0, 255);

  // TEMP+HUMIDITY AIR: read the input on digital pin 2:
  float humidity_air = dht.readHumidity();
  float temperature_air = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity_air) || isnan(temperature_air)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  if (humidity_soil<80){
    digitalWrite(9, HIGH);
  }
  else
  {
    digitalWrite(9, LOW);
  }

  //Fade the LED using the mapped value
  //analogWrite(9, sensorValue);

  // print out the values you read:
  Serial.print("Bodenfeucht_roh: ");
  Serial.print(humidity_soil_raw);
  Serial.print(" ; ");

  Serial.print("Bodenfeuchtigkeit: ");
  Serial.print(humidity_soil);
  Serial.print(" %;");

  Serial.print("Luftfeuchtigkeit: ");
  Serial.print(humidity_air);
  Serial.print(" %;");

  Serial.print("Lufttemperatur: ");
  Serial.print(temperature_air);
  Serial.println(" °C");
  delay(2000);        // delay in between reads for stability
}