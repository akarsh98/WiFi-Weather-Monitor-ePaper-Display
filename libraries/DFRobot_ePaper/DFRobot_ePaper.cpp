#include "DFRobot_ePaper.h"

unsigned char  *Buffer = new unsigned char[4000];
unsigned char  *DF_Display_bw = new unsigned char[2756];
unsigned char  *DF_Display_red = new unsigned char[2756];
unsigned char GDOControl[]={0x01,(yDot-1)%256,(yDot-1)/256,0x00}; //for 2.13inch
unsigned char softstart[]={0x0c,0xd7,0xd6,0x9d};
unsigned char Rambypass[] = {0x21,0x8f};        // Display update
unsigned char MAsequency[] = {0x22,0xf0};       // clock 
unsigned char GDVol[] = {0x03,0xea};            // Gate voltage +15V/-15V
unsigned char SDVol[] = {0x04,0x0a};            // Source voltage +15V/-15V
unsigned char VCOMVol[] = {0x2c,0xa8};          // VCOM 7c
unsigned char BOOSTERFB[] = {0xf0,0x1f};        // Source voltage +15V/-15V
unsigned char DummyLine[] = {0x3a,0x1a};        // 4 dummy line per gate
unsigned char Gatetime[] = {0x3b,0x08};         // 2us per line
unsigned char BorderWavefrom[] = {0x3c,0x33};   // Border
unsigned char RamDataEntryMode[] = {0x11,0x01}; // Ram data entry mode
eInk_dev epaPerdev;




DFRobot_ePaper::DFRobot_ePaper(uint16_t width, uint16_t height, uint8_t scandir, uint8_t ADDRESS, uint8_t id) : DFRobot_Display(width, height)
{
    epaPerdev.width = width;
    epaPerdev.highly = height;
    epaPerdev.scandir = scandir;
    Address = ADDRESS;
    epaPerID = id;
}

DFRobot_ePaper::~DFRobot_ePaper()
{}

void DFRobot_ePaper::drawPicture(const unsigned char *pic_bw = NULL, const unsigned char *pic_red = NULL)
{
    if(epaPerID == IL0376F_SPI){
        //The image data to be displayed is stored in the cache
        if(pic_bw == NULL){
            for(int i = 0; i < 2756; i++)
                DF_Display_bw[i] = 0;
        }else{
            for(int i = 0; i < 2756; i++)
                DF_Display_bw[i] = pic_bw[i];
        }
        if(pic_red == NULL){
        for(int i = 0; i < 2756; i++)
                DF_Display_red[i] = 0;
        }else{
            for(int i = 0; i < 2756; i++)
                DF_Display_red[i] = pic_red[i];
        }
    }else if(epaPerID == IL0376F_I2C){
        //uint16_t pj = 0;
        #ifdef __AVR__
        stateScan();int t1=micros();
        for(uint16_t i=0; i<212; i++){
            Wire.beginTransmission(Address); // transmit to device #8
            if(i == 0) Wire.write(DFR_IL0376F_DRAWPICTURE);
            if(i<106){
                for(unsigned char j = 0; j < 26; j++){
                    if(pic_bw == NULL){
                        Wire.write(0Xff);
                    }else{
                        Wire.write(~pgm_read_byte_near(pic_bw + 26*i+j));
                    }
                }
            }else{
                for(unsigned char j = 0; j < 26; j++){
                    if(pic_red == NULL){
                        Wire.write(0Xff);
                    }else{
                        Wire.write(~pgm_read_byte_near(pic_red + 26*i+j-2756));
                    }
                }
            }
            Wire.endTransmission();    // stop transmitting
        }int t2=micros();//Serial.print(t2-t1);Serial.println("(us)");
        #else
        stateScan();int t1=micros();
        for(uint16_t i=0; i<212; i++){
            Wire.beginTransmission(Address); // transmit to device #8
            if(i == 0) Wire.write(DFR_IL0376F_DRAWPICTURE);
            if(i<106){
                for(unsigned char j = 0; j < 26; j++){
                    if(pic_bw == NULL){
                        Wire.write(0Xff);
                    }else{
                        Wire.write(~pic_bw[26*i+j]);
                    }
                }
            }else{
                for(unsigned char j = 0; j < 26; j++){
                    if(pic_red == NULL){
                        Wire.write(0Xff);
                    }else{
                        Wire.write(~pic_red[26*i+j-2756]);
                    }
                }
            }
            Wire.endTransmission();    // stop transmitting
        }int t2=micros();//Serial.print(t2-t1);Serial.println("(us)");
        #endif
    }
}

void DFRobot_ePaper::drawPicture(const unsigned char *pic_bw_3895 = NULL)
{
    if(epaPerID == IL3895_I2C){
        //uint16_t pj = 0;
        #ifdef __AVR__
        stateScan();int t1=micros();
        for(uint16_t i=0; i<160; i++){
            Wire.beginTransmission(Address); // transmit to device #8
            if(i == 0) Wire.write(DFR_IL3895_DRAWPICTURE);
            for(unsigned char j = 0; j  <25; j++)
            {
                Wire.write(~pgm_read_byte_near(pic_bw_3895+ 25*i+j));
            }
            Wire.endTransmission();    // stop transmitting
        }int t2=micros();//Serial.print(t2-t1);Serial.println("(us)");
        #else
        stateScan();int t1=micros();
        for(uint16_t i=0; i<160; i++){
            Wire.beginTransmission(Address); // transmit to device #8
            if(i == 0) Wire.write(DFR_IL3895_DRAWPICTURE);
            for(unsigned char j = 0; j  <25; j++)
            {
                Wire.write(~pic_bw_3895[25*i+j]);
            }
            Wire.endTransmission();    // stop transmitting
        }int t2=micros();//Serial.print(t2-t1);Serial.println("(us)");
        #endif
    }else if(epaPerID == IL3895_SPI){
        if(pic_bw_3895 != NULL){
            for(int i  =0; i < 4000; i++)
                Buffer[i] = pic_bw_3895[i];
        }
    }
}

void DFRobot_ePaper::flush()
{
    if(epaPerID == IL0376F_SPI){
        if(epaPerdev.scandir == EINK_SCAN_DIR3){
            powerOn();
            spiWirteCmd(0x10);
            for(int i = 0; i < 2756; i++) spiWirteData(~DF_Display_bw[i]);
            spiWirteCmd(0x11);
            spiWirteCmd(0x13);
            for(int i = 0; i < 2756; i++) spiWirteData(~DF_Display_red[i]);
            spiWirteCmd(0x11);
            powerOff();
        }else if(epaPerdev.scandir == EINK_SCAN_DIR1){
            int16_t y=2743;
            powerOn();
            spiWirteCmd(0x10);
            while(y>=0){
                for(int i = 0; i < 13; i++) spiWirteData(~DF_Display_bw[y+i]);
                y-=13;
            }
            y=2743;
            spiWirteCmd(0x11);
            spiWirteCmd(0x13);
            while(y>=0){
                for(int i = 0; i < 13; i++) spiWirteData(~DF_Display_red[y+i]);
                y-=13;
            }
            spiWirteCmd(0x11);
            powerOff();
        }else if(epaPerdev.scandir == EINK_SCAN_DIR2){
            int16_t y=2755;
            powerOn();
            spiWirteCmd(0x10);
            while(y>=0){
                for(int i = 0; i < 13; i++) spiWirteData(~DF_Display_bw[y-i]);
                y-=13;
            }
            y=2755;
            spiWirteCmd(0x11);
            spiWirteCmd(0x13);
            while(y>=0){
                for(int i = 0; i < 13; i++) spiWirteData(~DF_Display_red[y-i]);
                y-=13;
            }
            spiWirteCmd(0x11);
            powerOff();
        }else if(epaPerdev.scandir == EINK_SCAN_DIR4){
            int16_t y=12;
            powerOn();
            spiWirteCmd(0x10);
            while(y<=2755){
                for(int i = 0; i < 13; i++) spiWirteData(~DF_Display_bw[y-i]);
                y+=13;
            }
            y=2755;
            spiWirteCmd(0x11);
            spiWirteCmd(0x13);
            while(y<=2755){
                for(int i = 0; i < 13; i++) spiWirteData(~DF_Display_red[y-i]);
                y+=13;
            }
            spiWirteCmd(0x11);
            powerOff();
        }
    }else if(epaPerID == IL0376F_I2C){
        uint8_t buf[1]={0};
        stateScan();
        i2cWrite(Address, DFR_IL0376F_FLUSH, buf, 1);
    }
}

void DFRobot_ePaper::clear(uint8_t color)
{
    uint8_t bw,red;
    if(epaPerID == IL0376F_SPI){
        if(color == WHITE){
            bw = 0x00; red = 0x00;
        }else if(color == RED){
            bw = 0x00; red = 0xff;
        }else if(color == BLACK){
            bw = 0xff; red = 0x00;
        }else{
            Serial.println("no color!");
            // return false;
        }
        for(int i = 0; i < 2756; i++){
            DF_Display_bw[i]=bw;
            DF_Display_red[i]=red;
        }
    }else if(epaPerID == IL3895_I2C){
        uint8_t buf[1]={color};
        stateScan();
        i2cWrite(Address, DFR_IL3895_CLEAR, buf, 1);
    }else if(epaPerID == IL3895_SPI){
        if(color == WHITE) for(uint16_t d=0;d<4000;d++)Buffer[d]=0xff;
        else if(color == BLACK) for(uint16_t d=0;d<4000;d++)Buffer[d]=0;
    }else if(epaPerID == IL0376F_I2C){
        uint8_t buf[1]={color};
        stateScan();
        i2cWrite(Address, DFR_IL0376F_CLEAR, buf, 1);
    }
}

void DFRobot_ePaper::fillScreen(uint16_t color)
{
    clear(color);
}

void DFRobot_ePaper::drawPixel(int16_t x, int16_t y, uint16_t color)
{
    if(epaPerID == IL0376F_SPI){
        uint8_t sx,sy;
        uint16_t sby;
        if(x>211 || y>103){
            Serial.println("Out of display!");
            return;
        }
        sx = 211-x;      sby = sx*13;
        sy = (y+1)/8;    sby += sy;
        sy = (y+1)%8;
        if(color == RED){//Red dot
            if(sy != 0){
                DF_Display_bw[sby] &= (~(int)pow(2,8-sy)); 
                DF_Display_red[sby] |= ((int)pow(2,8-sy)); 
            }else{
                DF_Display_bw[sby-1] &= 0xFE;
                DF_Display_red[sby-1] |= 0x01;
            }
            return;
        }else if(color == BLACK){//Black spots
            if(sy != 0){
                DF_Display_red[sby] &= (~(int)pow(2,8-sy)); 
                DF_Display_bw[sby] |= ((int)pow(2,8-sy)); 
            }else{
                DF_Display_red[sby-1] &= 0xFE;
                DF_Display_bw[sby-1] |= 0x01;
            }
            return;
        }else if(color == WHITE){//White dots
            if(sy != 0){
                DF_Display_bw[sby] &= (~(int)pow(2,8-sy)); 
                DF_Display_red[sby] &= (~(int)pow(2,8-sy)); 
            }else{
                DF_Display_bw[sby-1] &= 0xFE;
                DF_Display_red[sby-1] &= 0xFE;
            }
            return;
        }else if(color == LUCENCY){
            return;
        }else return;
    }else if(epaPerID == IL3895_I2C){
        uint8_t buf[3]={x, y, color};
        stateScan();
        i2cWrite(Address, DFR_IL3895_DRAWPOINT, buf, 3);
    }else if(epaPerID == IL0376F_I2C){
        uint8_t buf[3]={x, y, color};
        stateScan();
        i2cWrite(Address, DFR_IL0376F_DRAWPOINT, buf, 3);
    }else if(epaPerID == IL3895_SPI){
        if((x+1)>epaPerdev.width || (y+1)>epaPerdev.highly){
            Serial.println("(drawPoint)Out of display!");
            return;
        }
        uint16_t m;
        uint8_t sy;
        m=x*16+(y+1)/8;
        sy=(y+1)%8;
        if(color == WHITE){//白色
            if(sy != 0)  Buffer[m] |= (int)pow(2,8-sy);
            else  Buffer[m-1] |= (int)pow(2,0);
        }else if(color == BLACK){
            if(sy != 0)  Buffer[m] &= (~(int)pow(2,8-sy));
            else  Buffer[m-1] &= (~(int)pow(2,0));
        }else return;
        return;
    }
}

void DFRobot_ePaper::flush(uint8_t mode)
{
    if(epaPerID == IL3895_I2C){
        uint8_t buf[1]={mode};
        stateScan();
        i2cWrite(Address, DFR_IL3895_FLUSH, buf, 1);
    }else if(epaPerID == IL0376F_SPI){
        flush();
    }else if(epaPerID == IL0376F_I2C){
        flush();
    }else if(epaPerID == IL3895_SPI){
        if(mode == PART){
            initPart();
            disPart(0,xDot-1,0,yDot-1,(unsigned char *)Buffer);
        }else if(mode == FULL){
            initFull();
            disFull((unsigned char *)Buffer);
            delay(4000);
        }
    }
}


void DFRobot_ePaper::disString(uint8_t x, uint8_t y, uint8_t size, char *ch, uint8_t color)
{
    if(epaPerID == IL3895_I2C){
        //Serial.println(strlen(ch));Serial.println(ch[0],HEX);Serial.println(ch[1],HEX);
        uint16_t len=strlen(ch);
        uint8_t buf[len+4];
        buf[0] = x;
        buf[1] = y;
        buf[2] = size;
        buf[len+3] = color;
        for(uint16_t i=0; i<len; i++)
        {
            buf[3+i] = (uint8_t)ch[i];
        }
        if(len+4<30){
            for(uint16_t i=0; i<len+4; i++)
            stateScan();
            i2cWrite(Address, DFR_IL3895_DISSTRING, buf, len+4);
        }else{
            uint16_t quotient=(len+4)/30, remainder=(len+4)%30;
            uint8_t *P = buf;
            stateScan();
            i2cWriteByte(Address, DFR_IL3895_DISSTRING_START);
            for(uint16_t i=0; i<quotient; i++)
            {
                i2cWriteBuffer(Address, P, 30);
                P += 30;
            }
            if(remainder != 0){
                i2cWriteBuffer(Address, P, remainder);
            }
            i2cWriteByte(Address, DFR_IL3895_DISSTRING_END);
        }
    }else if(epaPerID == IL0376F_SPI){
        disStringIL0376FSPI(x, y, size, ch, color);
    }else if(epaPerID == IL0376F_I2C){
        //Serial.println(strlen(ch));Serial.println(ch[0],HEX);Serial.println(ch[1],HEX);
        uint16_t len=strlen(ch);
        uint8_t buf[len+4];
        buf[0] = x;
        buf[1] = y;
        buf[2] = size;
        buf[len+3] = color;
        for(uint16_t i=0; i<len; i++)
        {
            buf[3+i] = (uint8_t)ch[i];
        }
        if(len+4<30){
            for(uint16_t i=0; i<len+4; i++)
            stateScan();
            i2cWrite(Address, DFR_IL0376F_DISSTRING, buf, len+4);
        }else{
            uint16_t quotient=(len+4)/30, remainder=(len+4)%30;
            uint8_t *P = buf;
            stateScan();
            i2cWriteByte(Address, DFR_IL0376F_DISSTRING_START);
            for(uint16_t i=0; i<quotient; i++)
            {
                i2cWriteBuffer(Address, P, 30);
                P += 30;
            }
            if(remainder != 0){
                i2cWriteBuffer(Address, P, remainder);
            }
            i2cWriteByte(Address, DFR_IL0376F_DISSTRING_END);
        }
    }else if(epaPerID == IL3895_SPI){
        disStringIL3895SPI(x, y, size, ch, color);
    }
}

/********************IL0376F*********************/

void DFRobot_ePaper::powerOn(void)
{
    spiWirteCmd(0x06);//Set the boost
    spiWirteData(0x17);
    spiWirteData(0x17);
    spiWirteData(0x17);
    spiWirteCmd(0x04);//Access to electricity
    stateScan();
    spiWirteCmd(0X00);//Set sweeping direction
    spiWirteData(0xc3|epaPerdev.scandir);
    spiWirteCmd(0X50);
    spiWirteData(0x37);
    spiWirteCmd(0x30);//Set the PLL
    spiWirteData(0x39);
    setWindow(212,104);//Pixel setting 212*104
    spiWirteCmd(0x82);//Vcom setting
    spiWirteData (0x0a);
}

void DFRobot_ePaper::powerOff(void)
{
    stateScan();
    spiWirteCmd(0x12);
    delay(12000);
    spiWirteCmd(0x82);//to solve Vcom drop
    spiWirteData(0x00);
    spiWirteCmd(0x01);//power setting
    spiWirteData(0x02);
    spiWirteData(0x00);
    spiWirteData(0x00);
    spiWirteData(0x00);
    spiWirteCmd(0X02);//Power off
    delay(3000);
}


void DFRobot_ePaper::setWindow(uint16_t x, uint16_t y){
    uint8_t hres,vres_h,vres_l;
    hres = y/8;
    hres <<= 3; 
    vres_h = x>>8;
    vres_l = x&0xff;
    spiWirteCmd(0x61);
    spiWirteData(hres);
    spiWirteData(vres_h);
    spiWirteData(vres_l);
}

/********************IL3895*********************/

void DFRobot_ePaper::SetRamArea(unsigned char Xstart,unsigned char Xend,unsigned char Ystart,unsigned char Ystart1,unsigned char Yend,unsigned char Yend1)
{
    unsigned char RamAreaX[3];  // X start and end
    unsigned char RamAreaY[5];  // Y start and end  0,3,63,0,0,0
    RamAreaX[0] = 0x44; // command
    RamAreaX[1] = Xstart;
    RamAreaX[2] = Xend;
    RamAreaY[0] = 0x45; // command
    RamAreaY[1] = Ystart;
    RamAreaY[2] = Ystart1;
    RamAreaY[3] = Yend;
    RamAreaY[4] = Yend1;
    SetCmdDataIL3895(RamAreaX, sizeof(RamAreaX));
    SetCmdDataIL3895(RamAreaY, sizeof(RamAreaY));
}

void DFRobot_ePaper::SetRamPointer(unsigned char addrX,unsigned char addrY,unsigned char addrY1)
{
    unsigned char RamPointerX[2];// default (0,0)
    unsigned char RamPointerY[3];
    RamPointerX[0] = 0x4e;
    RamPointerX[1] = addrX;
    RamPointerY[0] = 0x4f;
    RamPointerY[1] = addrY;
    RamPointerY[2] = addrY1;
    SetCmdDataIL3895(RamPointerX, sizeof(RamPointerX));
    SetCmdDataIL3895(RamPointerY, sizeof(RamPointerY));
}

void DFRobot_ePaper::W21Init()
{
    SetCmdDataIL3895(GDOControl, sizeof(GDOControl));  // Pannel configuration, Gate selection 
    SetCmdDataIL3895(softstart, sizeof(softstart));  // X decrease, Y decrease
    SetCmdDataIL3895(VCOMVol, sizeof(VCOMVol));    // VCOM setting
    SetCmdDataIL3895(DummyLine, sizeof(DummyLine));  // dummy line per gate
    SetCmdDataIL3895(Gatetime, sizeof(Gatetime));    // Gage time setting
    SetCmdDataIL3895(RamDataEntryMode, sizeof(RamDataEntryMode));  // X increase, Y decrease
    SetRamArea(0x00,(xDot-1)/8,(yDot-1)%256,(yDot-1)/256,0x00,0x00);  // X-source area,Y-gage area
    SetRamPointer(0x00,(yDot-1)%256,(yDot-1)/256);// set ram
}

void DFRobot_ePaper::UpdatePart()
{
    spiWirteCmdDataIL3895(0x22,0x04);
    spiWirteCmdIL3895(0x20);
    spiWirteCmdIL3895(0xff);
}

void DFRobot_ePaper::UpdateFull()
{
    spiWirteCmdDataIL3895(0x22,0xc7);
    spiWirteCmdIL3895(0x20);
    spiWirteCmdIL3895(0xff);
}

void DFRobot_ePaper::disPart(unsigned char xStart,unsigned char xEnd,unsigned long yStart,unsigned long yEnd,unsigned char *DisBuffer)
{
    SetRamArea(xStart/8, xEnd/8, yEnd%256, yEnd/256, yStart%256, yStart/256);// X-source area,Y-gage area
    SetRamPointer(xStart/8, yEnd%256, yEnd/256);// set ram
    WriteDispRamIL3895(xEnd-xStart, yEnd-yStart+1,DisBuffer);
    UpdatePart();
    delay(300);
    SetRamArea(xStart/8, xEnd/8, yEnd%256, yEnd/256, yStart%256, yStart/256);// X-source area,Y-gage area
    SetRamPointer(xStart/8, yEnd%256, yEnd/256);// set ram
    WriteDispRamIL3895(xEnd-xStart, yEnd-yStart+1,DisBuffer);;
}

void DFRobot_ePaper::disFull(unsigned char *DisBuffer)
{
    SetRamPointer(0x00,(yDot-1)%256,(yDot-1)/256);  // set ram
    WriteDispRamIL3895(xDot, yDot, (unsigned char *)DisBuffer); // white
    UpdateFull(); 
}

void DFRobot_ePaper::WirteLUT(unsigned char *LUTvalue,unsigned char Size)
{
    SetCmdDataIL3895(LUTvalue, Size);
}

void DFRobot_ePaper::powerOnIL3895()
{
    spiWirteCmdDataIL3895(0x22,0xc0);
    spiWirteCmdIL3895(0x20);
}

void DFRobot_ePaper::initPart()
{
    #ifdef __ets__
    delayMicroseconds(1);
    #else 
    stateScanIL3895(); 
    #endif
    W21Init();
    WirteLUT((unsigned char *)LUTDefault_part,sizeof(LUTDefault_part));
    powerOnIL3895();
}

void DFRobot_ePaper::initFull()
{
    #ifdef __ets__
    delayMicroseconds(1);
    #else 
    stateScanIL3895(); 
    #endif
    W21Init();
    WirteLUT((unsigned char *)LUTDefault_full,sizeof(LUTDefault_full));
    powerOnIL3895();
}


