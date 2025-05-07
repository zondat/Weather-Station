#ifndef _WEATHER_FORECAST_HPP
#define _WEATHER_FORECAST_HPP

// #include <Arduino.h>
#include "displaymodule.hpp"
#include "node.hpp"

class AWeatherForecast {
  protected:
    INode *node = nullptr;
    IDisplayModule *displayModule = nullptr;
    String baseUrl = "http://api.openweathermap.org/data/2.5/weather?q=Hanoi,VN";
    
	public:
    virtual bool connectWifi(const char* ssid, const char* pw) = 0;
    virtual bool isConnected() = 0;
    virtual bool accessWebsite(String apiKey) = 0;
		virtual void update() = 0;
		virtual ~AWeatherForecast() = default;
};
#endif