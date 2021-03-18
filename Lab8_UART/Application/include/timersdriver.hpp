/*******************************************************************************
*  FILENAME:      timersdiver.hpp
*
*  DESCRIPTION:   This file contains declaration of a class `TimersDriver`   
*                 to use timers (class `Timer` in AbstractHardware folder). 
* 
******************************************************************************/

#ifndef _TIMERSDRIVER_HPP_
#define _TIMERSDRIVER_HPP_

#include "timers.hpp"
#include "timersconfig.hpp"

class TimersDriver
{
public: 
  void Config(std::uint16_t prescaler, std::uint16_t arr, 
    std::uint16_t counter);
  void Sleep(); 
}; 

#endif  // _TIMERSDRIVER_HPP_
