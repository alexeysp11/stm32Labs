/*******************************************************************************
*  FILENAME:      ledsdriver.hpp
*
*  DESCRIPTION:   This file contains a class `LedsDriver` and definition  
*                 for LEDs. 
* 
* Class `LedsDriver` inherits class `Singleton` and implements some methods 
* by using array of LEDs.
*
*  Copyright (c) 2018 by South Ural State University
******************************************************************************/

#ifndef LEDDRIVER_H
#define LEDDRIVER_H

#include "leds.hpp"             // for Led. 
#include "singleton.hpp"        // for Singleton. 
#include "gpioaregisters.hpp"   // for GPIOA. 
#include "gpiocregisters.hpp"   // for GPIOC. 
#include <array>                // for std::array. 


constexpr std::size_t ledsCount = 4U;     // Total number of LEDs. 

constexpr std::uint32_t led1Pin = 5U;     // Pin of LED 1 equal to 5. 
constexpr std::uint32_t led2Pin = 9U;     // Pin of LED 1 equal to 5. 
constexpr std::uint32_t led3Pin = 8U;     // Pin of LED 1 equal to 5. 
constexpr std::uint32_t led4Pin = 5U;     // Pin of LED 1 equal to 5. 


/*
* Enumeration of LEDs. 
*/ 
enum class LedNum
{
  led1 = 0,
  led2 = 1,
  led3 = 2,
  led4 = 3,
  ledMax = ledsCount - 1
};

/*
* Implements some methods by using array of LEDs (switching on and off all LEDs, 
* toggling all LEDs, getting a number of LEDs or a certain LED) and inherits
* class `Singleton`. 
* Stores an array of LEDs. 
* 
* Array of LEDs defined as a private parameter. 
*/
class LedsDriver : public Singleton<LedsDriver> 
{ 
  public:
    /*
    * Summary: switches on all LEDs in sequential way through all elements 
    * of array of LEDs. 
    */ 
    void SwitchOnAll()
    {
      for(auto it: leds)
      {
        it.get().SwitchOn();
      }
    };
    
    /*
    * Summary: switches off all LEDs in sequential way through all elements 
    * of array of LEDs. 
    */ 
    void SwitchOffAll()
    {
      for(auto it: leds)
      {
        it.get().SwitchOff();
      }
    };
    
    /*
    * Summary: implements sequential toggling LEDs (as a snake). 
    */ 
    void ToggleAll()
    {
      for(auto it: leds)
      {
        it.get().Toggle();
      }
    };
    
    /*
    * Summary: gets a number of LEDs.
    * 
    * Returns: number of elements in leds array.
    */
    std::size_t GetLedsCount()
    {
      return leds.size();
    };
    
    /*
    * Summary: gets LED by index (element of enum `LedNum`) in the array of LEDs. 
    * 
    * Parameters:   [num] - certain LED defined as an element of enum `LedNum`. 
    * 
    * Returns: a reference to an object of `ILed` structure. 
    */
    inline ILed& GetLed(LedNum num)
    {
      return leds[static_cast<std::size_t>(num)];
    }
    friend class Singleton<LedsDriver>;
  
  private:
    LedsDriver() = default;     
    std::array<std::reference_wrapper<ILed>, ledsCount> leds {
      Led<
        Pin<Port<GPIOA>,
            led1Pin,
            PinWriteable>
            >::GetInstance(),
      Led<
          Pin<Port<GPIOC>,
              led2Pin,
              PinWriteable>
              >::GetInstance(),
       Led<
           Pin<Port<GPIOC>,
               led3Pin,
               PinWriteable>
               >::GetInstance(),
       Led<
           Pin<Port<GPIOC>,
               led4Pin,
               PinWriteable>
               >::GetInstance()
                                    };
  
    
};

#endif
