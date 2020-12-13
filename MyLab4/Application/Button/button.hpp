#pragma once 
#include <cstdint>
#include "port.hpp"
#include "LED.hpp"

template<typename Reg>
class Button
{
  public:
    template<class T> void IsPressed(T) {}
    void ReactOnPushing()
    {
      static bool isPressed = 0;
      
      Port<Reg> port;
      
      if(port.IsPressed() && !isPressed)
      {
        while(port.IsPressed()); 
        
        isPressed = 1;
        
        LED<GPIOC, 5> led_1; 
        LED<GPIOC, 8> led_2; 
        LED<GPIOC, 9> led_3; 
        LED<GPIOA, 5> led_4; 
        
        led_1.Toggle();
        led_2.Toggle();
        led_3.Toggle();
        led_4.Toggle();
      }
      
      if(!port.IsPressed())
        isPressed = 0;
    }
};