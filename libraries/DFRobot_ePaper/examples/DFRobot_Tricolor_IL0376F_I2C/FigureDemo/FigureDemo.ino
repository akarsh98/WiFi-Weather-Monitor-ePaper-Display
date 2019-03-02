/*!
 * file FigureDemo.ino
 *
 * @n Once the program downloaded, ePaper will display some figures 
 * such as dotted lines,oblique lines, rectangle, filling rectangle 
 * region, round, filling round range.
 * It shows infrastructure functions of ePaper drawing.
 *
 * Copyright    [DFRobot](http://www.dfrobot.com), 2016
 * Copyright    GNU Lesser General Public License
 *
 * version  V0.1
 * date  2017-11-30
 */
 
#include "Arduino.h"
#include "DFRobot_IL0376F_I2C.h"
DFRobot_IL0376F_I2C epaper;

#define BUSY     D4

void setup(void)
{
    Serial.begin(115200);
    //Select the corresponding pins
    epaper.begin(BUSY);

    //Clear the screen and display white
    epaper.fillScreen(WHITE);
    //Displays a string, red font
    epaper.disString(0,0,1,"I2C",BLACK);

    //Let me draw a red dot
    for(uint8_t x=12,y=12; y<92; y+=2)
    {
        epaper.drawPixel(x,y,RED);
    }
    //Draw two lines
    epaper.drawLine(24,12, 36,92,RED);
    epaper.drawLine(36,12, 24,92,RED);
    //Draw a red rectangle
    epaper.drawRect(48,12, 30,80,RED);
    //Fill a rectangle with black
    epaper.fillRect(55,19, 16,66,BLACK);
    //Draw a hollow circle
    epaper.drawCircle(105,32, 20,RED);
    //Draw a solid circle
    epaper.fillCircle(105,32, 13,BLACK);
    //Draw a rounded rectangle
    epaper.drawRoundRect(85,57, 38,35, 10,RED);
    //Fill in a rounded rectangle
    epaper.fillRoundRect(90,62, 28,25, 8,BLACK);
    //Draw a triangle
    epaper.drawTriangle(149,12, 130,92, 169,92,RED);
    //Fill in a triangle
    epaper.fillTriangle(149,25, 135,87, 163,87,BLACK);
    //Prompt characters
    epaper.disString(177,12, 2,"图",BLACK);
    epaper.disString(177,55, 2,"形",BLACK);

    //Refresh screen display
    epaper.flush();
}

void loop(void)
{
    delay(8000);
}