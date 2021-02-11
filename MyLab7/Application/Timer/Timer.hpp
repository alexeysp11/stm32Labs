#pragma once
#include <cstdint>
#include "led.hpp"
#include "tim2registers.hpp"
#include "nvicregisters.hpp"

class Timer
{
public :
  void ChangeFrequency();
  void Start();
};