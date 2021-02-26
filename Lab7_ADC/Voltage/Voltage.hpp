// File Voltage.hpp contains declaration of a class Voltage. 
// Class Voltage implements interfaces ISubjectMeasurer and IMeasurer. 

#ifndef _STM32LABS_VOLTAGE_H_
#define _STM32LABS_VOLTAGE_H_

#include "Observers.hpp"        // for ISubjectMeasurer and IMeasurer. 
#include "Adc.hpp"

#include <cstdint>
#include <list>

static float V_REF = *reinterpret_cast < uint16_t* >(0x1FFF7A2A);
static float K = 0.0f;                  // Slope. 

class Voltage: public ISubjectMeasurer, public IMeasurer
{
public: 
  Voltage() = default; 
  void Run(); 
  float GetValue(); 
  void Subscribe(IObserverMeasurer& observer);
  void Unsubscribe(IObserverMeasurer& observer); 
private: 
  std::list<IObserverMeasurer*> _observers;
};

#endif