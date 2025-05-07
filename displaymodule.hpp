#ifndef _DISPLAY_MODULE_HPP
#define _DISPLAY_MODULE_HPP

#include <Arduino.h>

class IDisplayModule {
	public:
    virtual void switchMode() = 0;
		virtual void setup() = 0;
		virtual void clear() = 0;
		virtual void display(String text) = 0;
		virtual void display(const char** lines, int nLines) = 0;
		virtual void pause() = 0;
		virtual ~IDisplayModule() = default;
};
#endif