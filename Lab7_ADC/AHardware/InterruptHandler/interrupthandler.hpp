#ifndef REGISTERS_INTERRUPTHANDLER_HPP
#define REGISTERS_INTERRUPTHANDLER_HPP


#include "tim2registers.hpp" //for TIM2
#include "gpiocregisters.hpp" //for TIM2

class InterruptHandler {
public:
  static void DummyHandler() { while(true) {} }
};
#endif