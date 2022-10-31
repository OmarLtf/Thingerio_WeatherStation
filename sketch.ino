/**
   ESP32 + DHT22 Example for Wokwi
   
   https://wokwi.com/arduino/projects/322410731508073042
*/

#define THINGER_SERIAL_DEBUG

#define USERNAME "OmarLtf"
#define DEVICE_ID "PlatformTest"
#define DEVICE_CREDENTIAL "?09biyc1TrSvrnxS"


#include <ThingerESP32.h>
#include "DHTesp.h"
#include <WiFi.h>
const int DHT_PIN = 15;



DHTesp dhtSensor;
ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  // Serial.begin(9600);
  Serial.begin(115200);
  Serial.print("Connecting to WiFi");
  WiFi.begin("Wokwi-GUEST", "", 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");

  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  pinMode(18, OUTPUT);

  thing.add_wifi("Wokwi-GUEST", "");

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["LED"] << digitalPin(18);

  // resource output example (i.e. reading a sensor value)
  Serial.println(millis());

  // TempAndHumidity  data = dhtSensor.getTempAndHumidity();

  // float temp = data.temperature;
  // float hum = data.humidity;
  // Serial.println(dhtSensor.getTempAndHumidity().temperature);
  // Serial.println(dhtSensor.getTempAndHumidity().humidity);

  // Serial.println(temp);
  // Serial.println(hum);

  thing["Temperature"] >> outputValue(dhtSensor.getTempAndHumidity().temperature);
  thing["Humidity"] >> outputValue(dhtSensor.getTempAndHumidity().humidity);

  // more details at http://docs.thinger.io/arduino/


}

void loop() {
  // Serial.println("Temp: " + String(data.temperature, 2) + "°C");
  // Serial.println("Humidity: " + String(data.humidity, 1) + "%");
  // Serial.println("---");
  // delay(1000);
 
   thing.handle();
}