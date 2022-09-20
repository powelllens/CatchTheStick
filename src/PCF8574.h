#ifndef _PCF8574_H_
#define _PCF8574_H_

#include <Arduino.h>
#include <Wire.h>

#define PCF8574_CLOCK 100000

#define InitWire 1

class PCF8574
{
public:
    void init(int SDA, int SCL, int address);
    void pinMode(int pin, int mode);
    int digitalWrite(int pin, int value);
    int digitalRead(int pin);
    int digitalReadReg(int pin);
    int write(int reg);
    int read();
    void setSleep();
    void setDataAvaliable() { this->DataAvaliable = true; };
    bool getDataAvaliable() { return this->DataAvaliable; };
    void resetDataAvaliable() { this->DataAvaliable = false; };
    int getReg() { return reg; };

private:
    int address, reg = 255;
    TwoWire *wire;
    bool DataAvaliable = false;
};
#endif