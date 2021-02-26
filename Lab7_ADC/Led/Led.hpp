#ifndef _STM32LABS_LED_H_
#define _STM32LABS_LED_H_

#include "port.h"

class ILed
{
public:
  virtual ~ILed() {}
  virtual void SetHigh() = 0;
  virtual void SetLow() = 0;
  virtual void Toggle() = 0;
};

class Led: public ILed
{
public:
  Led(std::uint8_t num, IPortSet& aPin);
  ~Led();
  bool IsSet(); 
  void SetHigh();
  void SetLow(); 
  void Toggle();

private:
  std::uint8_t number; 
  IPortSet& port;
};

#endif