#include "esp32node.hpp"
#include <esp_now.h>
#include <WiFi.h>
#include <HTTPClient.h>

Esp32Node::Esp32Node() {
  WiFi.mode(WIFI_STA);
}

bool Esp32Node::connectWifi(const char* ssid, const char*  pw) {
  WiFi.begin(ssid, pw);
  return WiFi.status() == WL_CONNECTED;
}

bool Esp32Node::connectMesh() {
  if (esp_now_init() == ESP_OK) {
    // esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
    // esp_now_register_recv_cb(OnDataRecv);
    return true;
  }
  return false;
} 

bool Esp32Node::isConnectedToWifi() {
	return WiFi.status() == WL_CONNECTED;
}

String Esp32Node::httpGetRequest(const char* url) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, url);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    //Serial.print("HTTP Response code: ");
    //Serial.println(httpResponseCode);
    payload = http.getString();
  }
  //else {
    //Serial.print("Error code: ");
    //Serial.println(httpResponseCode);
  //}
  // Free resources
  http.end();

  return payload;
}