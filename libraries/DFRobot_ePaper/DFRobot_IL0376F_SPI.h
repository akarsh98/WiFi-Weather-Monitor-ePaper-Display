#include <Arduino.h>
#include <SPI.h> 
#include <String.h>
#include <math.h>
#include "DFRobot_ePaper.h"

#ifndef __DFRobot_IL0376F_SPI_H
#define __DFRobot_IL0376F_SPI_H
//speed
#define DFR_W21_SPI_SPEED   0x02
//Pin_operation
#define DFR_GT30_CS_0         digitalWrite(DFR_GT30_CS,LOW)
#define DFR_GT30_CS_1         digitalWrite(DFR_GT30_CS,HIGH)
#define DFR_W21_CS_0          digitalWrite(DFR_W21_CS,LOW)
#define DFR_W21_CS_1          digitalWrite(DFR_W21_CS,HIGH)
#define DFR_W21_DC_0          digitalWrite(DFR_W21_DC,LOW)
#define DFR_W21_DC_1          digitalWrite(DFR_W21_DC,HIGH)
//scan_direction
#define EINK_SCAN_DIR1        ((uint8_t)2<<2)//From left to right, top to bottom
#define EINK_SCAN_DIR2        ((uint8_t)0<<2)//From left to right, down to the top
#define EINK_SCAN_DIR3        ((uint8_t)3<<2)//From right to left, top to bottom
#define EINK_SCAN_DIR4        ((uint8_t)1<<2)//From right to left, down to top  
//Screen parameters
#define WIDTH    (uint16_t)212
#define HIGHLY   (uint16_t)104
#define SCANDIR  (uint8_t)EINK_SCAN_DIR3
#define ID       (uint8_t)0

class DFRobot_IL0376F_SPI : public DFRobot_ePaper
{
public:
    DFRobot_IL0376F_SPI();
    ~DFRobot_IL0376F_SPI();

    void        begin(const char cs_W21, const char cs_GT30, const char dc, const char busy);

private:
    void        spiRead(uint32_t addr, uint8_t len, char *ch);
    void        spiWriteByte(unsigned char value);
    void        spiWirteCmd(unsigned char command);
    void        spiWirteData(unsigned char data);
    void        spiDelay(unsigned char xsp);
    void        stateScan(void);
    void        disStringIL0376FSPI(uint8_t x, uint8_t y, uint8_t size, char *ch, uint8_t color);


    uint8_t     DFR_W21_CS;
    uint8_t     DFR_W21_DC;
    uint8_t     DFR_W21_BUSY;
    uint8_t     DFR_GT30_CS;
};

#endif
