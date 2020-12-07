#include "gpiocregisters.hpp" //for GPIOC
#include "gpioaregisters.hpp" //for GPIOA

class LightEmittingDiodes
{
  public: 
    static void ReactOnButton()
    {
      bool isPressed = false; 
      
      // If user pushed a button
      if(GPIOC::IDR::IDR13::Low::IsSet() && !isPressed)
      {
        isPressed = true;

        if(GPIOC::ODR::ODR5::Low::IsSet())
        {
          //LightEmittingDiodes::ToggleDiodes();
          LightEmittingDiodes::ChangeFrequency();
        }
        else
        {
          //LightEmittingDiodes::ToggleDiodes();
          LightEmittingDiodes::ChangeFrequency();
        }
      }
      
      if(GPIOC::IDR::IDR13::High::IsSet())
          isPressed = false;
    }
    
private:
    // I implemented ToggleDiodes() in order to ensure if buttons work correctly
    static void ToggleDiodes(bool on)
    {
      if(on == 1)
      {
        GPIOC::BSRR::BS5::High::Write();
        GPIOC::BSRR::BS9::High::Write();
        GPIOC::BSRR::BS8::High::Write();
        GPIOA::BSRR::BS5::High::Write();
      }
      else
      {
        GPIOC::BSRR::BR5::Low::Write();
        GPIOC::BSRR::BR9::Low::Write();
        GPIOC::BSRR::BR8::Low::Write();
        GPIOA::BSRR::BR5::Low::Write();
      }
    }
    
    static void ChangeFrequency()
    {
      int min = 50; 
      int max = 1000; 
      static int oldDelay_ms = 1000; 
      static bool forward = 0; 
      
      // Set new delay
      int newDelay_ms;
      if (forward == 0)
        newDelay_ms  = oldDelay_ms - 50; 
      else
        newDelay_ms  = oldDelay_ms + 50; 
      
      // If new delay is equal to min or max, change direction 
      if (newDelay_ms == min) 
        forward = 1; 
      if (newDelay_ms == max)
        forward = 0; 
      
      // Write new prescaler to TIM2_PSC
      int prescaler = TIM2::PSC::Get();
      int newPrescaler = prescaler * newDelay_ms / oldDelay_ms;
      TIM2::PSC::Write(newPrescaler); 
      oldDelay_ms = newDelay_ms;
    }
};
