// File LedsController.hpp contains definition of LedsController class. 

#ifndef _STM32LABS_LEDSCONTROLLER_H_
#define _STM32LABS_LEDSCONTROLLER_H_

#include "Observers.hpp"
#include "Led.hpp"

class LedsController: public IObserver
{
public: 
  LedsController(); 
  LedsController(Led* ledsArray); 
  void OnUpdate(ISubject& sender, std::uint8_t value); 
private: 
  Led* _ledsArray;
}; 

#endif