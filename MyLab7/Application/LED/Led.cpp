#include "Led.hpp"

Led::Led(uint8_t num, IPortSet& aPin): number(num), port(aPin)
{
}

void Led::Toggle()
{
   port.Toggle(number);
}