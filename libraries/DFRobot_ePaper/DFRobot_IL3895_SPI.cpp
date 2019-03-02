#include"DFRobot_IL3895_SPI.h"



DFRobot_IL3895_SPI::DFRobot_IL3895_SPI() : DFRobot_ePaper(WIDTH, HIGHLY, NULL, NULL, ID)
{}

DFRobot_IL3895_SPI::~DFRobot_IL3895_SPI()
{}


void DFRobot_IL3895_SPI::begin(const char cs_W21, const char cs_GT30,const char dc, const char busy)
{
    SPI.begin();
    DFR_W21_CS =cs_W21; DFR_W21_DC =dc;  DFR_GT30_CS = cs_GT30;  DFR_W21_BUSY = busy;
    pinMode(DFR_W21_CS, OUTPUT); 
    pinMode(DFR_W21_DC, OUTPUT);
    pinMode(DFR_GT30_CS, OUTPUT);
    pinMode(DFR_W21_BUSY, INPUT);
}

void DFRobot_IL3895_SPI::spiDelayIL3895(unsigned char xsp){
    unsigned char i;
    while(xsp--)
    {
        for(i=0;i<2;i++);
    }
}

void DFRobot_IL3895_SPI::stateScanIL3895(void)
{
    while(1){
        if(digitalRead(DFR_W21_BUSY) == 0){
            break;
        }
        delayMicroseconds(100);
    }
}

void DFRobot_IL3895_SPI::spiReadIL3895(uint32_t addr, uint8_t len, char *ch)
{
    DFR_GT30_CS_0;
    DFR_W21_CS_1;
    SPI.transfer(0x0b);
    SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
    SPI.transfer(0x00);
    while(len --) {
        *ch = SPI.transfer(0x00);
        ch ++;
    }
    DFR_GT30_CS_1;
}

void DFRobot_IL3895_SPI::spiWriteByteIL3895(unsigned char value){
    SPI.transfer(value);
}

void DFRobot_IL3895_SPI::spiWirteCmdIL3895(unsigned char command){
    spiDelayIL3895(1);
    DFR_W21_CS_0;
    DFR_GT30_CS_1;
    DFR_W21_DC_0;
    //SPI.setBitOrder(MSBFIRST);
    spiWriteByteIL3895(command);
    DFR_W21_CS_1;
}

void DFRobot_IL3895_SPI::spiWirteCmdDataIL3895(unsigned char command,unsigned char data)
{
    #ifdef __ets__
    delayMicroseconds(1);
    #else 
    stateScanIL3895(); 
    #endif
    DFR_W21_CS_0;
    DFR_GT30_CS_1;
    DFR_W21_DC_0;   // command write
    spiWriteByteIL3895(command);
    DFR_W21_DC_1;   // command write
    spiWriteByteIL3895(data);
    DFR_W21_CS_1;
}

void DFRobot_IL3895_SPI::SetCmdDataIL3895(unsigned char *value, unsigned char datalen)
{
    unsigned char i = 0;
    unsigned char *ptemp;
    ptemp = value;
    DFR_W21_CS_0;
    DFR_GT30_CS_1;
    DFR_W21_DC_0;   // command write
    spiWriteByteIL3895(*ptemp);
    ptemp++;
    DFR_W21_DC_1;   // data write  
    for(i= 0;i<datalen-1;i++) // sub the command
    {
        spiWriteByteIL3895(*ptemp);
        ptemp++;
    }
    DFR_W21_CS_1;
}

void DFRobot_IL3895_SPI::WriteDispRamIL3895(unsigned char XSize,unsigned int YSize,unsigned char *Dispbuff)
{
    int i = 0,j = 0;
    if(XSize%8 != 0)
    {
        XSize = XSize+(8-XSize%8);
    }
    XSize = XSize/8;
    #ifdef __ets__
    delayMicroseconds(72904);
    #else 
    stateScanIL3895(); 
    #endif
    DFR_W21_CS_0;
    DFR_GT30_CS_1;
    DFR_W21_DC_0;   //command write
    spiWriteByteIL3895(0x24);

    DFR_W21_DC_1;   //data write
    for(i=0;i<YSize;i++)
    {
      for(j=0;j<XSize;j++)
      {
        spiWriteByteIL3895(*Dispbuff);
        Dispbuff++;
      }
    }
    DFR_W21_CS_1;
}

void DFRobot_IL3895_SPI::disStringIL3895SPI(uint8_t x, uint8_t y, uint8_t size, char *ch, uint8_t color)
{
    DFR_W21_CS_1;
    GT30L_setCSPin(DFR_GT30_CS);
    setTextSize(size);
    supportChineseFont();
    setTextColor(color);
    setCursor(x,y);
    print(ch);
}



