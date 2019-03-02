#include"DFRobot_IL0376F_SPI.h"



DFRobot_IL0376F_SPI::DFRobot_IL0376F_SPI() : DFRobot_ePaper(WIDTH, HIGHLY, SCANDIR, NULL, ID)
{}

DFRobot_IL0376F_SPI::~DFRobot_IL0376F_SPI()
{}

void DFRobot_IL0376F_SPI::spiDelay(unsigned char xsp){
    unsigned char i;
    while(xsp--)
    {
        for(i=0;i<2;i++);
    }
}

void DFRobot_IL0376F_SPI::stateScan(void)
{
    while(1){
        if(digitalRead(DFR_W21_BUSY)==1){
            break;
        }
    }
}

void DFRobot_IL0376F_SPI::begin(const char cs_W21, const char cs_GT30,const char dc, const char busy)
{
    SPI.begin();
    DFR_W21_CS =cs_W21; DFR_W21_DC =dc;  DFR_GT30_CS = cs_GT30;  DFR_W21_BUSY = busy;
    pinMode(DFR_W21_CS, OUTPUT); 
    pinMode(DFR_W21_DC, OUTPUT);
    pinMode(DFR_GT30_CS, OUTPUT);
    pinMode(DFR_W21_BUSY, INPUT);
}

void DFRobot_IL0376F_SPI::spiRead(uint32_t addr, uint8_t len, char *ch)
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

void DFRobot_IL0376F_SPI::spiWriteByte(unsigned char value){
    SPI.transfer(value);
}

void DFRobot_IL0376F_SPI::spiWirteCmd(unsigned char command){
    spiDelay(1);
    DFR_W21_CS_0;
    DFR_GT30_CS_1;
    DFR_W21_DC_0;
    SPI.setBitOrder(MSBFIRST);
    spiWriteByte(command);
    DFR_W21_CS_1;
}

void DFRobot_IL0376F_SPI::spiWirteData(unsigned char data){
    spiDelay(1);
    DFR_W21_CS_0;
    DFR_GT30_CS_1;
    DFR_W21_DC_1;
    //If the scan method is 2 or 4, send a low post, then send a high post
    if(SCANDIR==EINK_SCAN_DIR2 || SCANDIR==EINK_SCAN_DIR4){
        SPI.setBitOrder(LSBFIRST);
    }else{//If the scan is 1 or 3, send the high first and post the low post
        SPI.setBitOrder(MSBFIRST);
    }
    spiWriteByte(data);
    DFR_W21_CS_1;
}


void DFRobot_IL0376F_SPI::disStringIL0376FSPI(uint8_t x, uint8_t y, uint8_t size, char *ch, uint8_t color)
{
    DFR_W21_CS_1;
    GT30L_setCSPin(DFR_GT30_CS);
    setTextSize(size);
    supportChineseFont();
    setTextColor(color);
    setCursor(x,y);
    print(ch);
}

// !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxwz{|}~
//Pixel cache
//     2743            0
//		|\   |\   |\   |
//		| \  | \  | \  |
//		|  \ |  \ |  \ |
//		|   \|   \|   \|
//     2755            12

