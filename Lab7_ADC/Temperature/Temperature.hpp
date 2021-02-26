// File Temperature.hpp contains declaration of Temperature class. 
// Class Temperature implements interfaces ISubjectMeasurer and IMeasurer. 

#ifndef _STM32LABS_TEMPERATURE_H_
#define _STM32LABS_TEMPERATURE_H_

#include "Observers.hpp"        // for ISubjectMeasurer and IMeasurer. 
#include "Adc.hpp"

#include <cstdint>
#include <list>

static uint16_t TS_CAL1 = *reinterpret_cast < uint16_t* >(0x1FFF7A2C);
static uint16_t TS_CAL2 = *reinterpret_cast < uint16_t* >(0x1FFF7A2E);

class Temperature: public ISubjectMeasurer, public IMeasurer
{
public: 
  Temperature() = default;
  void Run(); 
  float GetValue(); 
  void Subscribe(IObserverMeasurer& observer);
  void Unsubscribe(IObserverMeasurer& observer); 
private: 
  std::list<IObserverMeasurer*> _observers;
}; 

#endif