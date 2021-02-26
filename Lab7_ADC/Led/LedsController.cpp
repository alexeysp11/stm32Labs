// File LedsController.cpp contains implementation of LedsController class. 

#include "LedsController.hpp"

#include <cstdint>

LedsController::LedsController()
{
}

/*
* Constructor that takes an array of LEDs as a parameter. 
*/
LedsController::LedsController(Led* ledsArray)
{
  _ledsArray = ledsArray; 
}

/*
* value is a number of LEDs that should be. 
*/
void LedsController::OnUpdate(ISubject& sender, std::uint8_t value)
{ 
  std::uint8_t num_elements = sizeof(_ledsArray) / sizeof(_ledsArray[0]); 
  
  for (std::uint8_t i = 0; i < num_elements; i++)
  {
    if (i <= value)
    {
      _ledsArray[i].SetHigh();  // Set high. 
    }
    else
    {
      _ledsArray[i].SetLow();   // Set low. 
    }
  }
}