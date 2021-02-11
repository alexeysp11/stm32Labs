#pragma once

#include "Button.hpp"
#include "Led.hpp"
#include "Timer.hpp"
#include "portsconfig.h"
#include <array>

class ChristmasTree
{
public: 
  ChristmasTree(IButton* aButton);
  Timer timer;
  void Run();

private:
  IButton* button;
  std::array<Led, 4> leds;
  int i=0;
}; 

extern ChristmasTree ct;