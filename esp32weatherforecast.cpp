#include "esp32weatherforecast.hpp"
#include "esp32node.hpp"
#include "eink.hpp"
#include <Arduino_JSON.h>

typedef struct weather_message {
  String description;
  float temperature;
	float pressure;
  float humidity;
  float wind;
};

weather_message mess;

Esp32WeatherForecast::Esp32WeatherForecast() {
  node = new Esp32Node();
  displayModule = new EInk();
}

bool Esp32WeatherForecast::connectWifi(const char* ssid, const char* pw) {
  return node->connectWifi(ssid, pw);
}

bool Esp32WeatherForecast::isConnected() {
  return node->isConnectedToWifi();
}

bool Esp32WeatherForecast::accessWebsite(String apiKey) {
  String url = baseUrl + "&APPID=" + apiKey;
  String jsonRes = node->httpGetRequest(url.c_str());
  JSONVar resp = JSON.parse(jsonRes);
  bool isSucceed = false;
  
  // JSON.typeof(jsonVar) can be used to get the type of the var
  if (JSON.typeof(resp) == "undefined") return false;
  String desc = JSON.stringify(resp["weather"][0]["main"]);
  String tempStr = JSON.stringify(resp["main"]["temp"]);
  String pressureStr = JSON.stringify(resp["main"]["pressure"]);
  String humidityStr = JSON.stringify(resp["main"]["humidity"]);
  String windStr = JSON.stringify(resp["wind"]["speed"]);

  if (tempStr!=null) {
    mess.description = desc;
    mess.temperature = tempStr.toFloat();
    mess.pressure = pressureStr.toFloat();
    mess.humidity = humidityStr.toFloat();
    mess.wind = windStr.toFloat();
    isSucceed = true;
  }

  if (Serial) {
    Serial.println("Url: " + url);
    Serial.println("Description: " + desc);
    Serial.println("Response: " + jsonRes);
    Serial.println("Temperature: " + tempStr);
    Serial.println("Pressure: " + pressureStr);
    Serial.println("Humidity: " + humidityStr);
    Serial.println("Wind: " + windStr);
  }
  return isSucceed;
}
		
void Esp32WeatherForecast::update() {
  const int len = 5;
  const char **arr = new const char*[len];
  String temp = "Temp: " + String(mess.temperature - 273.15) + " *C";
  String humidity = "Humidity: " + String(mess.humidity) + "%";
  String wind = "Wind: " + String(mess.wind) + "m/s";
  arr[0] = "Loc: Hanoi";  // -1 marks end of row
  arr[1] = mess.description.c_str();
  arr[2] = temp.c_str();
  arr[3] = wind.c_str();
  arr[4] = humidity.c_str();
  displayModule->display(arr, len);
}