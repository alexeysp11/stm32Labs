// File Solver.hpp contains declaration of Solver class. 
// Class Solver implements interfaces IObserverMeasurer and ISubject. 

#ifndef _STM32LABS_SOLVER_H_
#define _STM32LABS_SOLVER_H_

#include "Observers.hpp"        // for IObserverMeasurer and ISubject. 

#include <cstdint>
#include <list>

static float TEMPERATURE = 0.0f; 
static float VOLTAGE = 0.0f; 

class Solver: public IObserverMeasurer, public ISubject
{
public: 
  Solver();
  Solver(ISubject& Sender); 
  void Subscribe(IObserver& observer); 
  void Unsubscribe(IObserver& observer); 
  void Run(ISubject& sender, float temp, float voltage, float K); 
  void OnUpdate(float temp, float voltage, float K); 
private: 
  std::list<IObserver*> _observers;
  std::uint8_t _value; 
}; 

#endif