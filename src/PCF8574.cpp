#include "pcf8574.h"

void PCF8574::init(int SDA, int SCL, int address)
{
    this->address = address;
    this->wire = &Wire;
#ifdef InitWire
    Wire.begin(static_cast<int>(SDA), static_cast<int>(SCL), static_cast<uint32_t>(PCF8574_CLOCK));
#endif
}

void PCF8574::pinMode(int pin, int mode)
{
    if (mode != OUTPUT)
        digitalWrite(pin, HIGH);
}

int PCF8574::digitalWrite(int pin, int value)
{
    int reg = this->getReg();
    int result = this->write(value ? reg | (1 << pin) : reg & ~(1 << pin));
    return result;
}

int PCF8574::digitalRead(int pin)
{
    return (this->read() & (1 << pin)) ? HIGH : LOW;
}

int PCF8574::write(int reg)
{
    this->wire->beginTransmission(address);
    this->wire->write(reg);
    int result = this->wire->endTransmission();
    if (result == 0)
        this->reg = reg;
    return result;
}

int PCF8574::read()
{
    int result = this->wire->requestFrom(this->address, 1);
    this->reg = this->wire->read();
    return this->reg;
}

int PCF8574::digitalReadReg(int pin)
{
    return (this->reg & (1 << pin)) ? HIGH : LOW;
}

void PCF8574::setSleep()
{
    //this->write(0x00);
}