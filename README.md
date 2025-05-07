# Weather-Station
Using esp32 to connect internet, get weather information and display in LCD ePaper 2.9 inch.  

![20250507_182045](https://github.com/user-attachments/assets/751b9127-2a13-4ff9-87b4-c4b4846cd53b)

The project is the combination of 3 subprojects:  
(1) A project to control ePaper LCD 2.9 inch and LCD Nokia (DisplayModule)  
(2) A project to control the internet access via Esp32 (Node)  
(3) The last project uses the two previous to access the destined weather forecast website and display  

# Instruction  
The project is an Arduino project.
1. Download necessary libraries: Nokia5110, esp32 (hardware), GxEPD2.  
See examples->GxEPD2->GxEPD2_WS_ESP32_Driver to see how to manipulate ePaper lcd.   
2. Create new libraries
- In the folder Documents/Arduino/libraries, create 2 folders: DisplayModule and Node
- In the folder DisplayModule: add the files:  displaymodule.hpp, eink.hpp, eink.cpp, lcd.hpp, lcd.cpp, Small_LCD_Fonts.h
- In the folder Node: add the files: node.hpp, esp32node.hpp, esp32node.cpp
3. Create project
- Create Arduino project named WeatherForecast
- add to the folder: config.h, weatherforecast.hpp, esp32weatherforecast.hpp, esp32weatherforecast.cpp, WeatherForecast.ino
  
