#include <Arduino.h>
#include <String.h>
#include <math.h>
#include <Wire.h>
#include "DFRobot_Display.h"
#include "DFRobot_GT30L.h"

#ifndef __DFRobot_ePaper_H
#define __DFRobot_ePaper_H

//Pin definition
#ifdef __AVR__
#define D2 2
#define D3 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7
#define D8 8
#endif

//scan_direction
/*! From left to right, top to bottom */
#define EINK_SCAN_DIR1        ((uint8_t)2<<2)

/*! From left to right, down to the top */
#define EINK_SCAN_DIR2        ((uint8_t)0<<2)

/*! From right to left, top to bottom */
#define EINK_SCAN_DIR3        ((uint8_t)3<<2)

/*! From right to left, down to top */
#define EINK_SCAN_DIR4        ((uint8_t)1<<2)

/*! color */
#define LUCENCY  0
#define WHITE    1
#define BLACK    2
#define RED      3

/*! Instruction set */
#define  DFR_IL3895_FLUSH                      1
#define  DFR_IL3895_CLEAR                      2
#define  DFR_IL3895_DRAWPICTURE                3
#define  DFR_IL3895_DISSTRING                  4
#define  DFR_IL3895_DRAWPOINT                  5
#define  DFR_IL3895_DRAWLINE                   6
#define  DFR_IL3895_DEAWRECTANGLE              7
#define  DFR_IL3895_DRAWCIRCLE                 8
#define  DFR_IL3895_DRAWFILLRECT               9
#define  DFR_IL3895_STANDBY                   10
#define  DFR_IL3895_DISSTRING_START          111
#define  DFR_IL3895_DISSTRING_END            112
#define  DFR_IL3895_DRAWVLINE                 13
#define  DFR_IL3895_DRAWHLINE                 14

/*! Instruction set */
#define  DFR_IL0376F_FLUSH                    15
#define  DFR_IL0376F_CLEAR                    16
#define  DFR_IL0376F_DRAWPICTURE              17
#define  DFR_IL0376F_DISSTRING                18
#define  DFR_IL0376F_DRAWPOINT                19
#define  DFR_IL0376F_DRAWLINE                 20
#define  DFR_IL0376F_DEAWRECTANGLE            21
#define  DFR_IL0376F_DRAWCIRCLE               22
#define  DFR_IL0376F_DRAWFILLRECT             23
#define  DFR_IL0376F_STANDBY                  24
#define  DFR_IL0376F_DISSTRING_START         111
#define  DFR_IL0376F_DISSTRING_END           113
#define  DFR_IL0376F_DRAWVLINE                27
#define  DFR_IL0376F_DRAWHLINE                28

/*! ePaper id */
#define IL0376F_SPI  0
#define IL3895_I2C   1
#define IL0376F_I2C  2
#define IL3895_SPI   3

/*! Black and white epaper screen size */
#define xDot 128
#define yDot 250

/*! refresh mode */
#define FULL     0
#define PART     1

const unsigned char LUTDefault_part[]={
0x32,  // command
0x18,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x0F,0x01,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
const unsigned char LUTDefault_full[]={
0x32,  // command
0x22,0x55,0xAA,0x55,0xAA,0x55,0xAA,
0x11,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x1E,0x1E,0x1E,0x1E,0x1E,
0x1E,0x1E,0x1E,0x01,0x00,0x00,0x00,0x00,
};

//eINK important parameters 
typedef struct{
    uint16_t highly;
    uint16_t width;
    uint8_t scandir;
}eInk_dev;

typedef bool InkScreen_Error;

class DFRobot_ePaper : public DFRobot_Display
{
public:

    DFRobot_ePaper(uint16_t width, uint16_t height, uint8_t scandir, uint8_t ADDRESS, uint8_t id);
    ~DFRobot_ePaper();

    /*! Refresh screen -> tricolor epaper */
    void             flush();

    /*! Refresh screen - black and white epaper */
    void             flush(uint8_t mode);

    /*! Display pictures -> tricolor epaper */
    void             drawPicture(const unsigned char *pic_bw, const unsigned char *pic_red);

    /*! Display pictures -> black and white epaper */
    void             drawPicture(const unsigned char *pic_bw_3895);

    /*! Display pictures -> black and white epaper */
    void             fillScreen(uint16_t color);

    /*! Draw a pixel on the screen */
    void             drawPixel(int16_t x, int16_t y, uint16_t color);

    /*! Displays a string */
    void             disString(uint8_t x, uint8_t y, uint8_t size, char *ch, uint8_t color);

private:

/********************IL0376F*********************/

    void             setWindow(uint16_t x, uint16_t y);
    void             powerOn(void);
    void             powerOff(void);
    void             clear(uint8_t color);

    virtual void     stateScan(void) {}
    virtual void     spiRead(uint32_t addr, uint8_t len, char *ch) {}
    virtual void     spiWriteByte(unsigned char value) {}
    virtual void     spiWirteCmd(unsigned char command) {}
    virtual void     spiWirteData(unsigned char data) {}
    virtual void     spiDelay(unsigned char xsp) {}
    virtual void     disStringIL0376FSPI(uint8_t x, uint8_t y, uint8_t size, char *ch, uint8_t color) {}

    virtual void     i2cWrite(unsigned char addr, unsigned char Reg, unsigned char *buf, unsigned char Num) {}
    virtual void     i2cWriteByte(unsigned char addr, unsigned char Cmd) {}
    virtual void     i2cWriteBuffer(unsigned char addr,  unsigned char *buf, unsigned char Num) {}


/********************IL3895*********************/

    void             SetRamArea(unsigned char Xstart,unsigned char Xend,unsigned char Ystart,unsigned char Ystart1,unsigned char Yend,unsigned char Yend1);
    void             SetRamPointer(unsigned char addrX,unsigned char addrY,unsigned char addrY1);
    void             W21Init();
    void             UpdatePart();
    void             UpdateFull();
    void             disPart(unsigned char xStart,unsigned char xEnd,unsigned long yStart,unsigned long yEnd,unsigned char *DisBuffer);
    void             disFull(unsigned char *DisBuffer);
    void             WirteLUT(unsigned char *LUTvalue,unsigned char Size);
    void             powerOnIL3895();
    void             initPart();
    void             initFull();

    virtual void     spiReadIL3895(uint32_t addr, uint8_t len, char *ch) {}
    virtual void     spiWriteByteIL3895(unsigned char value) {}
    virtual void     spiWirteCmdIL3895(unsigned char command) {}
    virtual void     spiDelayIL3895(unsigned char xsp) {}
    virtual void     spiWirteCmdDataIL3895(unsigned char command,unsigned char data) {}
    virtual void     SetCmdDataIL3895(unsigned char *value, unsigned char datalen) {}
    virtual void     WriteDispRamIL3895(unsigned char XSize,unsigned int YSize,unsigned char *Dispbuff) {}
    virtual void     disStringIL3895SPI(uint8_t x, uint8_t y, uint8_t size, char *ch, uint8_t color) {}
    virtual void     stateScanIL3895(void) {}


    uint8_t           Address;
    uint8_t           epaPerID;
};

#endif
