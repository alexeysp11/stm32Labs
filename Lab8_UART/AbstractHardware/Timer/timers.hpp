/*******************************************************************************
*  FILENAME:      timers.hpp
*
*  DESCRIPTION:   This file contains declaration of a class `Timers`. 
* 
******************************************************************************/

#ifndef _STM32LABS_TIMERS_HPP_
#define _STM32LABS_TIMERS_HPP_

#include "tim2registers.hpp"

class ITimerBase
{
public: 
  virtual void SetPrescaler(std::uint16_t psc) = 0; 
  virtual void SetArr(std::uint16_t arr) = 0; 
  virtual void SetCounter(std::uint16_t psc) = 0; 
  virtual void Sleep() = 0; 
};

template<typename TimReg>
class Timer : public ITimerBase
{
public: 
  void SetPrescaler(std::uint16_t psc) 
  {
    TimReg::PSC::Write(psc) ;
  }

  void SetArr(std::uint16_t arr) 
  {
    TimReg::ARR::Write(arr) ;
  }

  void SetCounter(std::uint16_t psc) 
  {
    TimReg::CNT::Write(psc) ;
  }

  // WHAT DOES IT MEAN? 
  void Config()
  {
    TimReg::SR::UIF::NoUpdate::Set();
    TimReg::CR1::CEN::Enable::Set() ;
  }

  void Sleep()
  {
    while(TimReg::SR::UIF::NoUpdate::IsSet());
    TimReg::SR::UIF::NoUpdate::Set();
  }
};

#endif  // _STM32LABS_TIMERS_HPP_