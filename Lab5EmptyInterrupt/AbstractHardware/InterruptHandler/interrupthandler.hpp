//
// Created by Sergey on 21.11.2019.
//

#ifndef REGISTERS_INTERRUPTHANDLER_HPP
#define REGISTERS_INTERRUPTHANDLER_HPP


#include "tim2registers.hpp"  //for TIM2
#include "gpioaregisters.hpp"  //for GPIOA
#include "gpiocregisters.hpp"  //for GPIOC

class InterruptHandler {
  public:
    static void DummyHandler() { for(;;) {} }
    
    static void MyTim2InterruptHandler()
    {
      if (TIM2::SR::UIF::UpdatePending::IsSet() && TIM2::DIER::UIE::Enable::IsSet())
      {
        TIM2::SR::UIF::NoUpdate::Set();
        
        static int i = 0; 
        static bool isForward = 1; 
        
        // Toggle LEDs
        switch(i)
        {
          case 0: 
            if(isForward == 1) 
            {
              i++;
            }
            else 
            { 
              i = 0; 
              isForward = 1; 
            }
            
            GPIOC::ODR::Toggle(1U << 5U);
            break;
          case 1: 
            if(isForward == 1) 
            {
              i++;
            }
            else 
            {
              i--;
            }
            
            GPIOC::ODR::Toggle(1U << 8U);
            break;
          case 2: 
            if(isForward == 1) 
            {
              i++;
            }
            else 
            {
              i--;
            }
            
            GPIOC::ODR::Toggle(1U << 9U);
            break;
          case 3: 
            if(isForward == 1) 
            { 
              i = 3; 
              isForward = 0; 
            }
            else 
            {
              i--;
            }
            
            GPIOA::ODR::Toggle(1U << 5U);
            break;
        }
      }
    }
};

#endif //REGISTERS_INTERRUPTHANDLER_HPP
