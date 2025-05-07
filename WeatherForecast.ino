#include "esp32weatherforecast.hpp"
#include "config.h"

Esp32WeatherForecast* forecastApp = nullptr;

void setup() {
  Serial.begin(115200);
  Serial.println("Init app...");
  
  forecastApp = new Esp32WeatherForecast();
  while (forecastApp->connectWifi(ssid, pw)) {
    Serial.println("Attempt wifi connection failed...");
    sleep(1000);
  }
  Serial.println("Wifi connected...");
}

void loop() {
  if (forecastApp->isConnected()) {
    if (forecastApp->accessWebsite(apiKey)) forecastApp->update();
  }
  delay(10000);
}
