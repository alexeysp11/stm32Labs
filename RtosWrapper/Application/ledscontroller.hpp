/*******************************************************************************
* Filename  	: ledscontroller.hpp
* 
* Details   	: Contains class `LedsController` that inherits `Singleton` 
*               class and implements different modes for LEDs. 
*
* Methods of classes defined in files "ledsmodes.hpp" and "ledsmode.hpp" 
* are actually called from `Update()` method in `LedsController` class
* (in this file).
* You can redefine all required modes (behaviors) in `LedsController` class. 
*
*******************************************************************************/

#ifndef LEDSCONTROLLER_H
#define LEDSCONTROLLER_H

#include "ledsdriver.hpp"   // for LedsDriver. 
#include "ledsmodes.hpp"    // for LedsMode. 
#include "singleton.hpp"    // for Singleton. 
#include <array>            // for std::array. 

/*
* This is kind of base class for implementing different modes of LEDs. 
*/ 
class LedsController : public Singleton<LedsController>
{
public:
  /*
  * Summary: executes required mode of LEDs. 
  * 
  * Parameters: [in] value - some value that is not used in the method. 
  */ 
  inline void Update(std::uint8_t value = 0)
  {
    modes[currentMode].get().Do(value);
  }
  
  /*
  * Changes a mode of LEDs. 
  */ 
  inline void NextMode()
  {
    currentMode++;
    
    if (currentMode >= modes.size())
    {
      currentMode = 0U;
    }
    
    modes[currentMode].get().Reset();
  }
  
  /* 
  * This function is used for explicit setting execution mode of LEDs. 
  */ 
  inline void SetMode(std::size_t mode)
  {
    currentMode = mode; 
  }
  
  friend class Singleton<LedsController>;
  
private:
  LedsController() = default;        
  std::size_t currentMode = 0U;   // By default a mode index is equal to 0, i.e. implement a tree.
  using tModesArray = std::array<std::reference_wrapper<LedsMode>, 7U>;    
  tModesArray modes = { 
                        LedsModeTree::GetInstance(),
                        LedsModeChess::GetInstance(),
                        LedsModeAll::GetInstance(),
                        LedsModeFirstPair::GetInstance(),
                        LedsModeInsideOutside::GetInstance(),
                        LedsModeAdc::GetInstance(), 
                        LedsModeFirst::GetInstance()
                      }; 
};

#endif //LEDSCONTROLLER_H
