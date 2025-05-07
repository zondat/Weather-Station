#ifndef _ESP32_WEATHER_FORECAST_HPP
#define _ESP32_WEATHER_FORECAST_HPP

// #include <Arduino.h>
#include "weatherforecast.hpp"

class Esp32WeatherForecast : public AWeatherForecast {
	public:
    Esp32WeatherForecast();
    bool connectWifi(const char* ssid, const char* pw) override;
    bool accessWebsite(String apiKey) override;
    bool isConnected() override;
		void update() override;
		virtual ~Esp32WeatherForecast() = default;
};
#endif