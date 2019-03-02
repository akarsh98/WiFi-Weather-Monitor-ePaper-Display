#include"DFRobot_IL0376F_I2C.h"


DFRobot_IL0376F_I2C::DFRobot_IL0376F_I2C (): DFRobot_ePaper(WIDTH, HIGHLY, NULL, A0, ID)
{
    Address = A0;
}

DFRobot_IL0376F_I2C::~DFRobot_IL0376F_I2C()
{}


void DFRobot_IL0376F_I2C::begin(const char busy)
{
    DFR_W21_BUSY = busy;
    Wire.begin();
    //Wire.setClock(100000);
    pinMode(DFR_W21_BUSY, INPUT);
    //digitalWrite(DFR_W21_BUSY, HIGH);
    //Serial.println(Address);
}

void DFRobot_IL0376F_I2C::stateScan()
{
    while(1){
        delay(1);Serial.println(digitalRead(DFR_W21_BUSY));
        if(digitalRead(DFR_W21_BUSY) == 0){
            break;
        }
    }
}

void DFRobot_IL0376F_I2C::i2cWrite(unsigned char addr, unsigned char Reg, unsigned char *buf, unsigned char Num)
{
    Wire.beginTransmission(addr); // transmit to device #8
    Wire.write(byte(Reg));              // sends one byte
    for(uint16_t i = 0; i  <Num; i++)
    {
        Wire.write(byte(buf[i])); 
    }
    Wire.endTransmission();    // stop transmitting
}

void DFRobot_IL0376F_I2C::i2cWriteByte(unsigned char addr, unsigned char Cmd)
{
    Wire.beginTransmission(addr); // transmit to device #8
    Wire.write(byte(Cmd));              // sends one byteS
    Wire.endTransmission();    // stop transmitting
}
void DFRobot_IL0376F_I2C::i2cWriteBuffer(unsigned char addr,  unsigned char *buf, unsigned char Num)
{
    Wire.beginTransmission(addr); // transmit to device #8
    for(uint16_t i = 0; i  <Num; i++)
    {
        Wire.write(byte(buf[i])); 
    }
    Wire.endTransmission();    // stop transmitting
}

void DFRobot_IL0376F_I2C::standby()
{
    uint8_t buf[1]={0};
    stateScan();
    i2cWrite(Address, DFR_IL3895_STANDBY, buf, 1);
}

void DFRobot_IL0376F_I2C::wakeUp()
{
    pinMode(DFR_W21_BUSY, OUTPUT);
    digitalWrite(DFR_W21_BUSY, HIGH);
    digitalWrite(DFR_W21_BUSY, LOW);
    begin(DFR_W21_BUSY);
}

void DFRobot_IL0376F_I2C::fillRect(int16_t x, int16_t y, int16_t width, int16_t height, 
                                            uint16_t color)
{
    uint8_t buf[5]={x, y, width, height, color};
    stateScan();
    i2cWrite(Address, DFR_IL0376F_DRAWFILLRECT, buf, 5);
}

void DFRobot_IL0376F_I2C::fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
    uint8_t buf[5]={x0, y0, r, 1, color};
    stateScan();
    i2cWrite(Address, DFR_IL0376F_DRAWCIRCLE, buf, 5);
}

