#include "Led.hpp"

Led::Led(uint8_t num, IPortSet& aPin): number(num), port(aPin)
{
}

Led::~Led() 
{
}

void Led::SetHigh()
{
   port.SetHigh(number);
}

void Led::SetLow()
{
   port.SetLow(number);
}

void Led::Toggle()
{
   port.Toggle(number);
}