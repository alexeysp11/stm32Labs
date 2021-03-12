/*******************************************************************************
* Filename  	: userbutton.hpp
* 
* Details   	: Contains definition and some implementation of a class `Button` 
*               that gets if a button is pressed or not. 
*
* Author      : Sergey Kolody
*******************************************************************************/

#ifndef __BUTTON_H
#define __BUTTON_H

#include "singleton.hpp"        // for Singleton.
#include "gpiocregisters.hpp"   // for GPIOC.
#include "pin.hpp"              // For Pin.
#include "port.hpp"             // For Port.
#include "susudefs.hpp"         // for __forcinline.

template<typename Pin>
class Button : public Singleton<Button<Pin>>
{
  friend class Singleton<Button<Pin>>;
public:
  __forceinline inline bool IsPressed() const
  {
    return (Pin::Get() != 1U);
  }

private:
  Button()
  {
  };
};

/* Button configuration: pin number of a button.
By default it is equal to 13 (port GPIOC). */
constexpr std::uint32_t buttonPin = 13U; 

/* Button configuration: set port for a button, pin number 
and that this pin is readable. */ 
using PinButton = Pin<Port<GPIOC>, buttonPin, PinReadable>;     

// Define `Button<PinButton>` as `UserButton` for simplicity.
using UserButton = Button<PinButton>;

#endif //__BUTTON_H
