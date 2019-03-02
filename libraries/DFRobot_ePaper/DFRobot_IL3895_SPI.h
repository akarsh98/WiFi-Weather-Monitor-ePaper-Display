#include <Arduino.h>
#include <SPI.h> 
#include <String.h>
#include <math.h>
#include "DFRobot_ePaper.h"

#ifndef __DFRobot_IL3895_SPI_H
#define __DFRobot_IL3895_SPI_H
//speed
#define DFR_W21_SPI_SPEED   0x02
//Pin_operation
#define DFR_GT30_CS_0         digitalWrite(DFR_GT30_CS,LOW)
#define DFR_GT30_CS_1         digitalWrite(DFR_GT30_CS,HIGH)
#define DFR_W21_CS_0          digitalWrite(DFR_W21_CS,LOW)
#define DFR_W21_CS_1          digitalWrite(DFR_W21_CS,HIGH)
#define DFR_W21_DC_0          digitalWrite(DFR_W21_DC,LOW)
#define DFR_W21_DC_1          digitalWrite(DFR_W21_DC,HIGH)
//Screen parameters
#define WIDTH                       (uint16_t)250
#define HIGHLY                      (uint16_t)122
#define ID            (uint8_t)3

class DFRobot_IL3895_SPI : public DFRobot_ePaper
{
public:
    DFRobot_IL3895_SPI();
    ~DFRobot_IL3895_SPI();

    void        begin(const char cs_W21, const char cs_GT30, const char dc, const char busy);

private:
    void        spiReadIL3895(uint32_t addr, uint8_t len, char *ch);
    void        spiWriteByteIL3895(unsigned char value);
    void        spiWirteCmdIL3895(unsigned char command);
    void        spiDelayIL3895(unsigned char xsp);
    void        spiWirteCmdDataIL3895(unsigned char command,unsigned char data);
    void        SetCmdDataIL3895(unsigned char *value, unsigned char datalen);
    void        WriteDispRamIL3895(unsigned char XSize,unsigned int YSize,unsigned char *Dispbuff);
    void        stateScanIL3895(void);
    void        disStringIL3895SPI(uint8_t x, uint8_t y, uint8_t size, char *ch, uint8_t color);

    uint8_t     DFR_W21_CS;
    uint8_t     DFR_W21_DC;
    uint8_t     DFR_W21_BUSY;
    uint8_t     DFR_GT30_CS;
};

#endif
