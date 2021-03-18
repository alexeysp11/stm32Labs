//
// Created by Sergey on 21.11.2019.
//

/*******************************************************************************
*  FILENAME:      interrupthandler.hpp
*
*  DESCRIPTION:   This file contains declaration of a class `InterruptHandler`.  
*
*  `InterruptHandler` class actually implements some methods to use UART via 
*  interrupts.  
*  Implementation is in `interrupthandler.cpp` file. 
*   
*  UART is defined in class `Uart` (AbstractHardware folder).
******************************************************************************/

#ifndef REGISTERS_INTERRUPTHANDLER_HPP
#define REGISTERS_INTERRUPTHANDLER_HPP

#include "tim2registers.hpp"            // for TIM2.
#include "gpiocregisters.hpp"           // for TIM2.

class InterruptHandler 
{
public:
  static void DummyHandler();
  static void Tim2ToggleLeds();
};

#endif //REGISTERS_INTERRUPTHANDLER_HPP
