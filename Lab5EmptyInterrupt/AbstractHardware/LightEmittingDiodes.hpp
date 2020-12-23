#include "gpiocregisters.hpp" //for GPIOC
#include "gpioaregisters.hpp" //for GPIOA

class LightEmittingDiodes
{
  public: 
    static void ReactOnButton()
    {
      static bool isPressed = 0; 
      
      // If user pushed a button
      if(GPIOC::IDR::IDR13::Low::IsSet() && !isPressed)
      {
        isPressed = 1;
        LightEmittingDiodes::ChangeFrequency();
      }
      
      if(GPIOC::IDR::IDR13::High::IsSet())
      {
        isPressed = 0;
      }
    }
    
private:
    static void ChangeFrequency()
    {
      int min = 49; 
      int max = 999; 
      
      // We assume that at initial point delay is equal to 1000 ms. 
      // So variable called isForward should be equal to 1 at initial point 
      // because a few steps later we need to toggle it. 
      static bool isForward = 1; 
      int currentDelay_ms = TIM2::ARR::Get();
      
      // If this function was invoked, you should anyway update TIM2_CNT.
      TIM2::CNT::Write(0);
      
      // If delay is equal to min or max, change direction and start counting from zero.
      if (TIM2::ARR::Get() == min || TIM2::ARR::Get() == max) 
      {
        isForward = !isForward; 
      }
      
      // Set new delay.
      if (isForward == 0)
      {
        TIM2::ARR::Write(TIM2::ARR::Get() - 50); 
      }
      else
      {
        TIM2::ARR::Write(TIM2::ARR::Get() + 50); 
      }
    }
};
