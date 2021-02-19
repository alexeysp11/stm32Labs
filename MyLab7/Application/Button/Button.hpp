#pragma once
#include "Port.hpp"

class IButton
{
public:
  virtual ~IButton() {}
  virtual bool IsPressed() = 0;
};

class Button : public IButton
{
public:
  Button(uint8_t num, IPortGet& aPin);
  
  bool IsPressed();

private:
  uint8_t number; 
  IPortGet& pin;
};