#include "DHT.h"

#include <Adafruit_NeoPixel.h>

#define PIN 13


Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);


#define DHTPIN 14     // what digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11

int soil = 26;
int water_motor = 27;

DHT dht(DHTPIN, DHTTYPE);

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  pinMode(water_motor, OUTPUT);

  strip.begin(); 
  strip.show(); 
  colorWipe(strip.Color(100, 0, 0), 50); //빨간색 출력
  
  dht.begin();
}

// the loop routine runs over and over again forever:
void loop() {

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  // read the input on analog pin 0:
  int sensorValue = analogRead(soil);

  
 

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }


  // print out the value you read:
  Serial.print("sensor 1 : ");
  Serial.print(sensorValue);
  Serial.print(" %\t");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.println(" %\t");

  if(sensorValue <= 20){
     digitalWrite(water_motor, HIGH);  
  }
  else{
    digitalWrite(water_motor, LOW);    // turn the LED off by making the voltage LOW
  }
  
  delay(2000);        // delay in between reads for stability
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
