#ifndef _LCD_HPP
#define _LCD_HPP

#include "displaymodule.hpp"

class NokiaLCD : public IDisplayModule {
	private:
		bool background = false;
    String formatText(const String &input);
    bool isValid(const String &text);

public:
    NokiaLCD();
		void setup() override;
		void switchMode() override;
		void display(String text) override;
		void display(const char** lines, int nLines) override;
		void pause() override;
		void clear() override;
		
};
#endif