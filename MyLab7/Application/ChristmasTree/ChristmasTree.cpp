#include "ChristmasTree.hpp"

ChristmasTree::ChristmasTree(IButton* aButton): button(aButton), leds {
                                                      Led(5, portC),
                                                      Led(8, portC),
                                                      Led(9, portC),
                                                      Led(5, portA)
                                                     }
{
}

void ChristmasTree::Run()
{
  timer.Start();
  
  while(true)
  {
    if(button->IsPressed())
    {
      timer.ChangeFrequency();
    }
  }
}

void ChristmasTree::Update()
{
  leds[i].Toggle();
  i = (i + 1) & 0x3;
}