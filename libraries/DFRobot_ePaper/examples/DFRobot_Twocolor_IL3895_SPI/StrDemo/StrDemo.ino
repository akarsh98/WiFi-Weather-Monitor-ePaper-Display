/*!
 * file StrDemo.ino
 *
 * @n The FireBeetle -ePaper Display Module has a built-in font chip that can display 
 * both Chinese and English.
 * Once the program downloaded, ePaper will display two lines of strings that 
 * shows ePaper basic string display. Users just need to call function: 
 * disString and random strings display are available. String colors, 
 * size and coordinate are adjustable.
 *
 * Copyright    [DFRobot](http://www.dfrobot.com), 2016
 * Copyright    GNU Lesser General Public License
 *
 * version  V0.1
 * date  2017-11-30
 */

#include "Arduino.h"
#include "DFRobot_IL3895_SPI.h"
DFRobot_IL3895_SPI epaper;

#define EPAPER_CS  D3
#define Font_CS  D6
#define EPAPER_DC  D8
#define EPAPER_BUSY     D7

void setup(void)
{
    Serial.begin(115200);
    //Select the corresponding pins
    epaper.begin(EPAPER_CS, Font_CS, EPAPER_DC, EPAPER_BUSY);

    //Clear the screen and display white
    epaper.fillScreen(WHITE);
    //Refresh screen display
    epaper.flush(FULL);

    //Displays a string, black font
    epaper.disString(0,0,1,"SPI",BLACK);
    //Refresh screen display
    epaper.flush(PART);

    //Displays a string, black font
    epaper.disString(41,12,1,"DFRobot黑白电子墨水屏",BLACK);
    //Refresh screen display
    epaper.flush(PART);

    //Displays a string, black font
    epaper.disString(57,40,1,"《+-*/=!@#$%&*(》",BLACK);
    //Refresh screen display
    epaper.flush(PART);

    //Display large font
    epaper.disString(61,65,2,"大号字体",BLACK);
    //Refresh screen display
    epaper.flush(PART);
}

void loop(void)
{
    delay(8000);
}