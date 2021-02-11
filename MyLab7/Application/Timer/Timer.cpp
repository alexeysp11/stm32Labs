#include "Timer.hpp"

void Timer::ChangeFrequency()
{
  int min = 49;
  int max = 999;

  // We assume that at initial point delay is equal to 1000 ms.
  // So variable called isForward should be equal to 1 at initial point
  // because a few steps later we need to toggle it.
  static bool isForward = 1;

  // If this function was invoked, you should anyway update TIM2_CNT.
  TIM2::CNT::Write(0);

  // If delay is equal to min or max, change direction.
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

void Timer::Start()
{
  TIM2::CR1::CEN::Enable::Set();
}