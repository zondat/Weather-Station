#ifndef _EINK_HPP
#define _EINK_HPP

#include "displaymodule.hpp"

class EInk: public IDisplayModule {
	private:
		uint8_t cs = 15, dc = 4, rst = 2, busy = 5;
		uint16_t background, foreground;
		uint8_t lineSpace = 3;
		uint16_t utx, uty, tbh = 15;
		
public:
    EInk();
    EInk(uint8_t cs, uint8_t dc, uint8_t rst, uint8_t bs);

		void setup() override;
		void switchMode() override;
		void display(String text) override;
		void display(const char** lines, int nLines) override;
		void pause() override;
		void clear() override;
		
    uint16_t getPages();
		void setPinCS(uint8_t p) {cs = p;}
		void setPinDC(uint8_t p) {dc = p;}
		void setPinRST(uint8_t p) {rst = p;}
		void setPinBS(uint8_t p) {busy = p;}
};
#endif