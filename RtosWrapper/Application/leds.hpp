/*******************************************************************************
* Filename  	: leds.hpp
* 
* Details   	: Contains definition of an abstract base structure `ILed` and  
*               class `Led`. 
*
* Class `Led` implements methods for setting, resetting and toggling a pin.
*
* Author      : Sergey Kolody
*******************************************************************************/

#ifndef LEDS_H
#define LEDS_H

#include "gpiocregisters.hpp"   // for GPIOC.
#include "pin.hpp"              // for Pin.
#include "singleton.hpp"        // for Singleton. 

/*
* Abstract structure for using methods `SwitchOn()`, `SwitchOff()`
* and `Toggle()` of a class `Led`. 
*/
struct ILed
{
  virtual void SwitchOn() = 0;

  virtual void SwitchOff() = 0;

  virtual void Toggle() = 0;

};

/*
* Contains methods for setting, resetting and toggling a pin. 
*/
template<typename Pin>
class Led : public ILed, public Singleton<Led<Pin>>
{
  friend class Singleton<Led<Pin>>;

public:
  __forceinline void SwitchOn() override
  {
    Pin::Set();
  };

  __forceinline void SwitchOff() override
  {
    Pin::Reset();
  };

  __forceinline void Toggle() override
  {
    Pin::Toggle();
  };

private:
  Led()
  {
  }
};

#endif // LEDS_H
