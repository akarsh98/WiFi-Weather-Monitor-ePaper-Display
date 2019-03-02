#include <Arduino.h>
#include <Wire.h>
#include <String.h>
#include <math.h>
#include "DFRobot_ePaper.h"

#ifndef __DFRobot_IL0376F_I2C_H
#define __DFRobot_IL0376F_I2C_H

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
#define  DFR_IL0376F_DISSTRING_START          111
#define  DFR_IL0376F_DISSTRING_END            113
#define  DFR_IL0376F_DRAWVLINE                27
#define  DFR_IL0376F_DRAWHLINE                28
/*! Address selection */
#define A0   0x30>>1
#define A1   0x38>>1
#define A2   0x3C>>1
#define A3   0x3E>>1
/*! Screen parameters */
#define LUCENCY  0
#define WHITE    1
#define BLACK    2
#define RED      3
/*! Screen parameters */
#define WIDTH                       (uint16_t)212
#define HIGHLY                      (uint16_t)104
#define ID                          (uint8_t)2


class DFRobot_IL0376F_I2C : public DFRobot_ePaper
{
public:
    DFRobot_IL0376F_I2C();
    ~DFRobot_IL0376F_I2C();

    /*! Set busy pins */
    void        begin(const char busy);

    /*! Standby mode */
    void        standby();

    /*! Standby awaken */
    void        wakeUp();

    /*! Fill the rectangle */
    void        fillRect(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);

    /*! Fill the circle */
    void        fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);


private:
    void        stateScan();
    void        i2cWrite(unsigned char addr, unsigned char Reg, unsigned char *buf, unsigned char Num);
    void        i2cWriteByte(unsigned char addr, unsigned char Cmd);
    void        i2cWriteBuffer(unsigned char addr,  unsigned char *buf, unsigned char Num);

    uint8_t     Address;
    uint8_t     DFR_W21_BUSY;
};

#endif

