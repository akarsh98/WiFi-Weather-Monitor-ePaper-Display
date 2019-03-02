# FireBeetle Covers-ePaper Display Module(SPI)

![SVG1](https://raw.githubusercontent.com/DFRobot/binaryfiles/master/DFR0511/DFR0511svg1.png)

# FireBeetle Covers-ePaper Display Module(I2C)

![SVG1](https://raw.githubusercontent.com/DFRobot/binaryfiles/master/DFR0511/DFR0511svg1.png)

## DFRobot_ePaper Library for Arduino

It provides an Arduino library to control 4 types of e-link display screen.  
The library compromises 4 drive modes of two epapers, including IIC drive, SPI drive of both Black & White epaper and Tricolor epaper.

## Table of Contents

* [Summary](#summary)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [Depends](#depends)
* [Tool](#tool)
* [History](#history)
* [Credits](#credits)
<snippet>
<content>

## Summary

The library is used to control Black & White epaper and Tricolor epaper screens to display graphics, images and text. And there are two drive modes to select.

## Methods


```C++

/*!
 * @brief Select the corresponding pins -> tricolor epaper
 *
 * @param cs_W21  Select spi cs pin
 *     D3: Piece of selected pin
 *     D4: Piece of selected pin
 * @param cs_GT30  Select the word library chip cs pins
 *     D5: Piece of selected pin
 *     D6: Piece of selected pin
 * @param dc  Select spi dc pin
 *     D8: Piece of selected pin
 * @param busy  Select spi busy pin
 */
void begin(const char cs_W21, const char cs_GT30, const char dc, busy);

/*!
 * @brief Select the corresponding pins -> black and white epaper
 *
 * @param busy Select I2C busy pin
 */
void begin(const char busy);

/*!
 * @brief Refresh screen -> tricolor epaper
 */
void flush(void);

/*!
 * @brief Refresh screen -> black and white epaper
 *
 * @param mode  The refresh mode
 *     PART: Local refresh
 *     FULL: Global refresh
 */
void flush(uint8_t mode);

/*!
 * @brief Image display -> tricolor epaper
 *
 * @param pic_bw  Black and white part
 *        pic_red  The red part
 */
void drawPicture(const unsigned char *pic_bw, const unsigned char *pic_red);

/*!
 * @brief Image display -> black and white epaper
 *
 * @param pic  Black and white part
 */
void drawPicture(const unsigned char *pic);

/*!
 * @brief Display string
 *
 * @param (x,y)  coordinate
 *        size  The font size
 *        *ch  The string to display
 *        color  BLACK or WHITE or RED
 */
void disString(uint8_t x, uint8_t y, uint8_t size, char *ch, uint8_t color);

/*!
 * @brief fill screen
 */
void fillScreen(uint16_t color);

/*!
 * @brief draw a pixel
 *
 * @param x       x-axis coordinates
 *        y       y-axis coordinates
 */
void drawPixel(int16_t x, int16_t y, uint16_t color);

/*!
 * @brief draw a line
 *
 * @param x0        The x-axis of the starting point
 *        y0        The y-axis of the starting point
 *        x1        The x-axis of the terminal point
 *        y1        The y-axis of the terminal point
 */
void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, 
              uint16_t color);

/*!
 * @brief draw a horizontal line
 *
 * @param x         The x-axis of the starting point
 *        y         The y-axis of the starting point
 *        width     The line lenth
 */
void drawHLine(int16_t x, int16_t y, int16_t width, uint16_t color);

/*!
 * @brief draw a vertical line
 *
 * @param x         The x-axis of the starting point
 *        y         The y-axis of the starting point
 *        height    The line lenth
 */
void drawVLine(int16_t x, int16_t y, int16_t height, uint16_t color);

/*!
 * @brief draw a rectangle
 *
 * @param x         The x-axis of the starting point
 *        y         The y-axis of the starting point
 *        width     The rectangle width
 *        height    The rectangle height
 */
void drawRect(int16_t x, int16_t y, int16_t width, int16_t height, 
              uint16_t color);

/*!
 * @brief draw a fill rectangle
 *
 * @param x         The x-axis of the starting point
 *        y         The y-axis of the starting point
 *        width     The rectangle width
 *        height    The rectangle height
 */
void fillRect(int16_t x, int16_t y, int16_t width, int16_t height, 
              uint16_t color);

/*!
 * @brief draw a circle
 *
 * @param x         The x-axis of the center
 *        y         The y-axis of the center
 *        r         The circle radius 
 */
void drawCircle(int16_t x, int16_t y, int16_t r, uint16_t color);

/*!
 * @brief draw a fill circle
 *
 * @param x         The x-axis of the center
 *        y         The y-axis of the center
 *        r         The circle radius
 */
void fillCircle(int16_t x, int16_t y, int16_t r, uint16_t color);

/*!
 * @brief draw a triangle
 *
 * @param x0        The x-axis of the first point
 *        y0        The y-axis of the first point
 *        x1        The x-axis of the second point
 *        y1        The y-axis of the second point
 *        x2        The x-axis of the third point
 *        y2        The y-axis of the third point
 */
void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, 
                  int16_t x2, int16_t y2, uint16_t color);
                  
/*!
 * @brief draw a fill triangle
 *
 * @param x0        The x-axis of the first point
 *        y0        The y-axis of the first point
 *        x1        The x-axis of the second point
 *        y1        The y-axis of the second point
 *        x2        The x-axis of the third point
 *        y2        The y-axis of the third point
 */
void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, 
                  int16_t x2, int16_t y2, uint16_t color);

/*!
 * @brief draw a rounded rectangle
 *
 * @param x         The x-axis of the starting point
 *        y         The y-axis of the starting point
 *        width     The rectangle width
 *        height    The rectangle height
 *        r         The rounded corner radius
 */
void drawRoundRect(int16_t x, int16_t y, int16_t, width, int16_t height, 
                   int16_t r, uint16_t color);
                   
/*!
 * @brief draw a fill rounded rectangle
 *
 * @param x         The x-axis of the starting point
 *        y         The y-axis of the starting point
 *        width     The rectangle width
 *        height    The rectangle height
 *        r         The rounded corner radius
 */
void fillRoundRect(int16_t x, int16_t y, int16_t, width, int16_t height, 
                   int16_t r, uint16_t color);


```

## Compatibility

FireBeetle Covers-ePaper Display Module(SPI):

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
FireBeetle-ESP32  |      √       |             |            | 
FireBeetle-ESP8266  |      √       |             |            | 
FireBeetle-BLE4.1 |              |      √      |            | 
Arduino uno |              |      √      |            | 
Arduino leonardo |              |      √      |            | 

FireBeetle Covers-ePaper Display Module(I2C):

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
FireBeetle-ESP32  |      √       |             |     Picture fetching       | 
FireBeetle-ESP8266  |      √       |             |            | 
FireBeetle-BLE4.1 |      √       |             | Select the "C" array           | 
Arduino uno |      √       |             |            | 
Arduino leonardo |      √       |             |            | 
 
## Depends

Projects           |                     URL                       | Remarks
------------------ | :-------------------------------------------: | -----------
DFRobot_Display        |  https://github.com/DFRobot/DFRobot_Display     | must

## Tool
### Picture fetching software USES tutorials
* ``Note:`` You need an image conversion software. [Download](https://raw.githubusercontent.com/DFRobot/DFRobot_ePaper/master/tool/lcd-image-converter.zip)(lcd-image-converter)<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The image size of black and white epaper is 250×122.<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The image size of the tricolor epaper is 212×104.<br>
* `1. Open a picture“xxx.jpg”. File->Open` <br>
![image](https://github.com/DFRobot/DFRobot_ePaper/blob/master/images/icon/File-Open.png)
* `2. Set the image to flip. Image->Rotate->180` <br>
![image](https://github.com/DFRobot/DFRobot_ePaper/blob/master/images/icon/Image-Rotate-180.png)
* `3. Open the output parameter Settings menu. Options->Conversion` <br>
![image](https://github.com/DFRobot/DFRobot_ePaper/blob/master/images/icon/Options-Conversion.png)
* `4. Set the parameters as shown below.` <br>
![image](https://github.com/DFRobot/DFRobot_ePaper/blob/master/images/icon/Parameter%20Settings.png)
* `5. After setting the parameters, click Show Preview`. <br>
![image](https://github.com/DFRobot/DFRobot_ePaper/blob/master/images/icon/Show%20Preview.png)
* `6. Copy the binary in the dialog box to the array in the demo.` <br> 
![image](https://github.com/DFRobot/DFRobot_ePaper/blob/master/images/icon/C.png)
* `7. Then, download the program to your development board and the image will appear on the screen.` <br> 

## History

- data 2017-12-01
- version V0.1

## Credits

Written by LiXin(1035868977@qq.com), 2017. (Welcome to our [website](https://www.dfrobot.com/))
