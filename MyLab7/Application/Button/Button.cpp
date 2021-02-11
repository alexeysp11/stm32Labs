#include "Button.hpp"

Button::Button(uint8_t num, IPortGet& aPin): number(num), pin(aPin)
{
}

bool Button::IsPressed()
{
  return (!pin.IsSet());
}