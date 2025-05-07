#include "lcd.hpp"
#include <Nokia_LCD.h>
#include "Small_LCD_Fonts.h"

uint8_t LINE_LEN_MAX = 21;
uint8_t LINE_COUNT_MAX = 6;

Nokia_LCD lcd(/* CLK */ 13 , 
                  /* DIN */ 12, 
                  /* DC */  11, 
                  /* CE */  10, 
                  /* RST */  9,
                  /* BL */   8);

NokiaLCD::NokiaLCD() {
  setup();
}


void NokiaLCD::setup() {
  lcd.begin();
  lcd.setBacklight(background);
  lcd.setContrast(60);  
  lcd.clear();
  lcd.setFont(&Small_LCD_Fonts::SmallFont);
}

void NokiaLCD::switchMode() {
  background = !background;
  lcd.setBacklight(background);
}

void NokiaLCD::display(const char** lines, int nLines) {


}

void NokiaLCD::display(String text) {
  lcd.setCursor(0, 0);
  if (isValid(text)) {
    lcd.print(text.c_str());
  } else {
    lcd.print("Text is too large");
  }
}

void NokiaLCD::pause() {}

void NokiaLCD::clear() {
  lcd.clear();
}


bool NokiaLCD::isValid(const String &text) {
    unsigned int currentLineLength = 0;
    unsigned int lineNumber = 1;
    
    for (unsigned int i = 0; i < text.length(); i++) {
        char c = text.charAt(i);
        
        if (c == '\n') {
            if (currentLineLength > LINE_LEN_MAX) {
                return false;
            }
            currentLineLength = 0;
            lineNumber++;
        } else {
            currentLineLength++;
            if (currentLineLength > LINE_LEN_MAX) {
                if (lineNumber>LINE_COUNT_MAX)
                  return false;
            }
        }
    }
    
    return true;
}

String NokiaLCD::formatText(const String &input) {
    String output;
    int currentLineLength = 0;
    int lastSpacePos = -1;
    
    for (int i = 0; i < input.length(); i++) {
        char c = input.charAt(i);
        
        if (c == '\n') {
            // Reset counters on newline
            output += c;
            currentLineLength = 0;
            lastSpacePos = -1;
            continue;
        }
        
        output += c;
        currentLineLength++;
        
        // Track the last space position
        if (c == ' ') {
            lastSpacePos = i;
        }
        
        // Check if we need to break the line
        if (currentLineLength >= LINE_LEN_MAX) {
            // If we found a space in this line, break there
            if (lastSpacePos != -1) {
                // Find the position of that space in our output
                int outputSpacePos = output.length() - (i - lastSpacePos) - 1;
                output.setCharAt(outputSpacePos, '\n');
                currentLineLength = i - lastSpacePos;
            } else {
                // No space found, force break
                output += '\n';
                currentLineLength = 0;
            }
            lastSpacePos = -1;
        }
    }
    
    return output;
}

// void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
//   memcpy(&cmd, incomingData, sizeof(cmd));
//   // if (cmd.reset || cmd.clear) clear();
//   // else {
//   //   display(cmd.mess);
//   // }
// }