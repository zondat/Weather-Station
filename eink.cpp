#include "EInk.hpp"

// #include <ESP8266WiFi.h>
// #include <espnow.h>
#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <GxEPD2_4C.h>
#include <GxEPD2_7C.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include "bitmaps/Bitmaps128x296.h" // 2.9"  b/w
#include "bitmaps/Bitmaps3c128x296.h" // 2.9"  b/w/r

#define GxEPD2_BW_IS_GxEPD2_BW true
#define GxEPD2_3C_IS_GxEPD2_3C true
#define GxEPD2_7C_IS_GxEPD2_7C true
#define GxEPD2_1248_IS_GxEPD2_1248 true
#define IS_GxEPD(c, x) (c##x)
#define IS_GxEPD2_BW(x) IS_GxEPD(GxEPD2_BW_IS_, x)
#define IS_GxEPD2_3C(x) IS_GxEPD(GxEPD2_3C_IS_, x)
#define IS_GxEPD2_7C(x) IS_GxEPD(GxEPD2_7C_IS_, x)
#define IS_GxEPD2_1248(x) IS_GxEPD(GxEPD2_1248_IS_, x)
#define USE_HSPI_FOR_EPD
#define ENABLE_GxEPD2_GFX 0

#define GxEPD2_DRIVER_CLASS GxEPD2_290 
#define GxEPD2_DISPLAY_CLASS GxEPD2_BW

#if defined(ESP32)
  #define MAX_DISPLAY_BUFFER_SIZE 65536ul // e.g.
  #if IS_GxEPD2_BW(GxEPD2_DISPLAY_CLASS)
    #define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))
    #elif IS_GxEPD2_3C(GxEPD2_DISPLAY_CLASS)
    #define MAX_HEIGHT(EPD) (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8) ? EPD::HEIGHT : (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8))
    #elif IS_GxEPD2_7C(GxEPD2_DISPLAY_CLASS)
    #define MAX_HEIGHT(EPD) (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE) / (EPD::WIDTH / 2) ? EPD::HEIGHT : (MAX_DISPLAY_BUFFER_SIZE) / (EPD::WIDTH / 2))
  #endif

  #if defined(USE_HSPI_FOR_EPD)
    SPIClass hspi(HSPI);
  #endif

  GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> device(GxEPD2_DRIVER_CLASS(/*CS=*/ 15, /*DC=*/ 27, /*RST=*/ 26, /*BUSY=*/ 25));
#endif

EInk::EInk() {
  background = GxEPD_WHITE;
  foreground = GxEPD_BLACK;
  setup();
}

EInk::EInk(uint8_t cs, uint8_t dc, uint8_t rst, uint8_t bs) : EInk() {
  setPinCS(cs);
  setPinDC(dc);
  setPinRST(rst);
  setPinBS(bs);
}

void EInk::setup() {
  #if defined(ESP32) && defined(USE_HSPI_FOR_EPD)
    hspi.begin(13, 12, 14, 15); // remap hspi for EPD (swap pins)
    device.epd2.selectSPI(hspi, SPISettings(4000000, MSBFIRST, SPI_MODE0));
  #endif
  
  device.init(115200);
  device.setRotation(1);
  device.clearScreen();
  
  device.fillScreen(background); 
  device.setTextColor(foreground);
  device.setFont(&FreeMonoBold9pt7b);
  
  device.setPartialWindow(0, 0, device.width(), device.height());
  device.firstPage();

  utx = 5;
  uty = 10 + lineSpace;
  do {
	const char* auth = "Autho:Zondat";
	device.fillScreen(background); 
	device.setTextColor(foreground);
	device.setCursor(utx, uty);
	device.print(auth);
	
	const char* intro = "Veri he'nso`m";
	uty += (tbh + lineSpace);
	device.setCursor(utx, uty);
	device.print(intro);
  } 
  while (device.nextPage());

  uty += (tbh + lineSpace);
}

void EInk::switchMode() {
  if (background == GxEPD_BLACK) {
    background = GxEPD_WHITE;
    foreground = GxEPD_BLACK;
  } else {
    background = GxEPD_BLACK;
    foreground = GxEPD_WHITE;
  }

  device.fillScreen(background); 
  device.setTextColor(foreground); 
}

void EInk::display(const char** lines, int nLines) {
	device.firstPage();
	utx = 5;
	uty = 10;
	do {
		for (int i=0; i<nLines; i++) {
			uint16_t nuty = uty + i * (tbh + lineSpace);
			device.setCursor(utx, nuty);
			device.print(lines[i]);
		}
	}
	while (device.nextPage());
}

void EInk::display(String text) {
  int16_t x, y;
  uint16_t w, h;

  device.firstPage();  
  do {
    device.getTextBounds(text, 0, 0, &x, &y, &w, &h);
    x = ((device.width() - w) / 2) - x;
    y = ((device.height() - h) / 2) - y;
    device.setCursor(x, y);
    device.print(text);
  } while (device.nextPage());
  //device.hibernate();
}

uint16_t EInk::getPages() {
  return device.pages();
}

void EInk::pause() {
  device.hibernate();
}

void EInk::clear() {
  device.clearScreen();
}
