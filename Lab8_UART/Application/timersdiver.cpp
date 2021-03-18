
#include "timersdriver.hpp"

void TimersDriver::Config(std::uint16_t prescaler, std::uint16_t arr, 
  std::uint16_t counter)
{
  tim2.SetPrescaler(prescaler); 
  tim2.SetArr(arr); 
  tim2.SetCounter(counter); 
}

void TimersDriver::Sleep()
{
  tim2.Sleep(); 
}