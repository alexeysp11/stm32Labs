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
        static int forward = 1; 
        
        // Toggle LEDs
        switch(i)
        {
          case 0: 
            if(forward == 1) i++;
            else { i = 0; forward = 1; };
            GPIOC::ODR::Toggle(1U << 5U);
            break;
          case 1: 
            GPIOC::ODR::Toggle(1U << 8U);
            if(forward == 1) i++;
            else i --;
            break;
          case 2: 
            GPIOC::ODR::Toggle(1U << 9U);
            if(forward == 1) i++;
            else i --;
            break;
          case 3: 
            GPIOA::ODR::Toggle(1U << 5U);
            if(forward == 1) { i = 3; forward = 0; }
            else i --;
            break;
        }
      }
    }
};

#endif //REGISTERS_INTERRUPTHANDLER_HPP
