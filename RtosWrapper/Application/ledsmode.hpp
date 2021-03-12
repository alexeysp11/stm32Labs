/*******************************************************************************
*  FILENAME:      ledsmode.hpp
*
*  DESCRIPTION:   This file contains a a base class `LedsMode` for all  
*                 LEDs modes. 
* 
* Includes ledsdriver.hpp which contains a class `LedsDriver` and definition  
* for LEDs.
*
*  Copyright (c) 2021 by South Ural State University
******************************************************************************/

#ifndef LEDSMODE_H
#define LEDSMODE_H

#include "ledsdriver.hpp"

/*
* Base class for all LEDs modes. 
* 
* Methods of this class can be overriden by child classes. 
*/ 
class LedsMode 
{
public:
  /*
  * Summary: starts to execute some of LEDs mode. 
  *
  * This method is actually called from `Update()` method in 
  * `LedsController` class. 
  * 
  * Remarks: can be overridden in `LedsModes` class where you can redifine 
  * implementation of different LEDs modes. 
  */
  virtual void Do(std::uint8_t value = 0U) 
  {
    LedsDriver::GetInstance().ToggleAll();
  } 
  
  /*
  * Stops to execute all of LEDs mode by switching off all LEDs in 
  * sequential way through all elements of array of LEDs. 
  */
  virtual void Reset()
  {
    LedsDriver::GetInstance().SwitchOffAll();
    currentLed = 0U;
  }
protected:
  std::size_t currentLed = 0U; 
  LedsMode() = default;
};

#endif //LEDSMODE_H