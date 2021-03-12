/*******************************************************************************
* Filename  	: ledsmodes.hpp
* 
* Details   	: Contains classes starting to execute some of LEDs mode. 
*               These classes inherit `LedsMode` class (file "ledsmode.hpp")
*               and `Singleton` class (file "singleton.hpp"). 
*
* Methods of classes defined in this file are actually called from 
* `Update()` method in `LedsController` class (file "ledscontroller.hpp").
* You can redefine all required modes (behaviors) in this class. 
*
* If you have not redefined any method of a class representing a mode, 
* the program is going to execute default `Do()` and `Reset()` methods from 
* LedsMode class. 
*
*******************************************************************************/

#ifndef LEDSMODES_H
#define LEDSMODES_H

#include "ledsdriver.hpp"
#include "ledsmode.hpp"
#include "singleton.hpp"

/*
* Sequentially toggles LEDs. 
*/ 
class LedsModeTree : public LedsMode, public Singleton<LedsModeTree>
{
  friend class Singleton<LedsModeTree>;
  public:
    /*
    * Summary: sequentially toggles LEDs (from 0 to 3, when index is equal to 4
    * it gets equal to 0 again and so on).
    * Just toggle one particular LED in one cycle according to index and then 
    * increment index. 
    * 
    * Parameters:   [in] value - some value (it is not used in the method). 
    * 
    * Remarks: gets an instance of `LedsDriver` class switches off all LEDs 
    * and switches on LEDs 1 and 3. 
    */ 
    virtual void Do(std::uint8_t value) override
    {
      LedsDriver& driver = LedsDriver::GetInstance();
      if (currentLed >= driver.GetLedsCount())
      {
        currentLed = 0U;
      }
      driver.GetLed(static_cast<LedNum>(currentLed)).Toggle();
      currentLed++;      
    } 
  private:
    LedsModeTree() = default;
};

/*
* Toggles LEDs 1 and 3, inherits classes `LedsMode` and `Singleton`.
*/ 
class LedsModeChess : public LedsMode, public Singleton<LedsModeChess>
{
  friend class Singleton<LedsModeChess>;
  public:
    /*
    * Summary: toggles LEDs 1 and 3.
    * 
    * Parameters:   [in] value - some value (it is not used in the method). 
    * 
    * Remarks: gets an instance of `LedsDriver` class, switches off all LEDs 
    * and switches on LEDs 1 and 3. 
    */ 
    virtual void Do(std::uint8_t value) override
    {
      LedsDriver & driver = LedsDriver::GetInstance();  // An instance of `LedsDriver` class. 
      
      driver.SwitchOffAll();
      driver.GetLed(LedNum::led1).SwitchOn();
      driver.GetLed(LedNum::led3).SwitchOn();
    }
  private:
    LedsModeChess() = default;  
};

/*
* Implements default `Do()` and `Reset()` methods. 
*/ 
class LedsModeAll : public LedsMode, public Singleton<LedsModeAll>
{
  friend class Singleton<LedsModeAll>;
  private:
    LedsModeAll() = default;  
};


/*
* Toggles LEDs 1 and 2, inherits classes `LedsMode` and `Singleton`.
*/ 
class LedsModeFirstPair : public LedsMode, public Singleton<LedsModeFirstPair>
{
  friend class Singleton<LedsModeFirstPair>;
  public:
    /*
    * Summary: toggles LEDs 1 and 2.
    * 
    * Parameters:   [in] value - some value (it is not used in the method). 
    * 
    * Remarks: gets an instance of `LedsDriver` class switches off all LEDs 
    * and switches on LEDs 1 and 2. 
    */ 
    virtual void Do(std::uint8_t value) override
    {
      LedsDriver & driver = LedsDriver::GetInstance();  // An instance of `LedsDriver` class. 
      driver.SwitchOffAll();
      driver.GetLed(LedNum::led1).SwitchOn();
      driver.GetLed(LedNum::led2).SwitchOn();
    }
   private:
    LedsModeFirstPair() = default;  
};

/*
* Toggles LEDs 2 and 3, inherits classes `LedsMode` and `Singleton`.
*/ 
class LedsModeInsideOutside : public LedsMode, public Singleton<LedsModeInsideOutside>
{
  friend class Singleton<LedsModeInsideOutside>;
  public:
    /*
    * Summary: toggles LEDs 2 and 3.
    * 
    * Parameters:   [in] value - some value (it is not used in the method). 
    * 
    * Remarks: gets an instance of `LedsDriver` class toggles LEDs 2 and 3. 
    */ 
    virtual void Do(std::uint8_t value) override
    {
      // An instance of `LedsDriver` class. 
      LedsDriver& driver = LedsDriver::GetInstance();
      
      driver.GetLed(LedNum::led2).Toggle();     // Toggle LED 2. 
      driver.GetLed(LedNum::led3).Toggle();     // Toggle LED 3. 
    }
   private:
    LedsModeInsideOutside() = default;  
};

class LedsModeAdc : public LedsMode, public Singleton<LedsModeAdc>
{
  friend class Singleton<LedsModeAdc>;
  public:
    virtual void Do(std::uint8_t value) override
    {
      LedsDriver & driver = LedsDriver::GetInstance(); 
      for (std::size_t i = 0U; i < driver.GetLedsCount(); i++)
      {
        if (i < value)
        {
          driver.GetLed(static_cast<LedNum>(i)).SwitchOn();
        } 
        else
        {
          driver.GetLed(static_cast<LedNum>(i)).SwitchOff();
        }
      }          
    }
    private:
    LedsModeAdc() = default;  
};

/*
* Allows to toggle only first LED. 
*/
class LedsModeFirst : public LedsMode, public Singleton<LedsModeFirst>
{
  friend class Singleton<LedsModeFirst>;
  public:
    /*
    * Summary: toggles only LED 1.
    * 
    * Parameters:   [in] value - some value (it is not used in the method). 
    * 
    * Remarks: gets an instance of `LedsDriver` class toggles LED 1. 
    */ 
    virtual void Do(std::uint8_t value = 0U) override
    {
      // An instance of `LedsDriver` class. 
      LedsDriver& driver = LedsDriver::GetInstance();
      
      driver.GetLed(LedNum::led1).Toggle();     // Toggle LED 1.         
    }
    private:
    LedsModeFirst() = default;  
};

#endif //LEDSMODES_H
