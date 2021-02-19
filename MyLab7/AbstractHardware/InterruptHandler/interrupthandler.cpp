#include "interrupthandler.hpp"

void InterruptHandler::DummyHandler()
{
  while(true); 
}

void InterruptHandler::Tim2Handler()
{
  if (TIM2::SR::UIF::UpdatePending::IsSet()) 
  { 
    TIM2::SR::UIF::NoUpdate::Set();
    ct.Update();
  }
}