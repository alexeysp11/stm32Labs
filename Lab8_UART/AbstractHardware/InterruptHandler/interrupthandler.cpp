/*******************************************************************************
*  FILENAME:      interrupthandler.cpp
*
*  DESCRIPTION:   This file contains implementation of methods of a class 
*                 `InterruptHandler`.  
*
*  `InterruptHandler` class actually implements some methods to use UART via 
*  interrupts.  
*   
*  UART is defined in class `Uart` (AbstractHardware folder).
******************************************************************************/

#include "interrupthandler.hpp"

/*
* Implements infinite `for` loop. 
*/
void InterruptHandler::DummyHandler() 
{ 
  for(;;) 
  {
  } 
}

/*
* Implements LEDs toggling using TIM2 timer. 
*/
void InterruptHandler::Tim2ToggleLeds()
{
  if (TIM2::SR::UIF::UpdatePending::IsSet())
  {
    TIM2::SR::UIF::NoUpdate::Set();
    GPIOC::ODR::Toggle(1 << 8) ;
  }
}
