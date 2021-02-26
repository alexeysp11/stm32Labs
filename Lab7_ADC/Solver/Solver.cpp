// File Solver.cpp contains implementation of Solver class. 

#include "Solver.hpp"

Solver::Solver()
{
  _value = 0; 
}

/*
* Adds new observer to the list of IObserver. 
*/
void Solver::Subscribe(IObserver& observer)
{
   _observers.push_back(&observer);
}

/*
* Removes an observer from the list of IObserver. 
*/
void Solver::Unsubscribe(IObserver& observer)
{
  _observers.remove(&observer);
}

/*
* Gets data from measuring devices and notifies Solver::Run if both 
* temperature and voltage were measured. 
*/
void Solver::OnUpdate(float temp, float voltage, float K)
{
  if (temp != NULL)
  {
    TEMPERATURE = temp; 
  }
  
  if (voltage != NULL)
  {
    VOLTAGE = voltage;
  }
  
  if (TEMPERATURE != NULL && VOLTAGE != NULL && K != 0)
  {
    this->Run((*this), TEMPERATURE, VOLTAGE, K);
  }
}

/*
* Executes methods of class Solver. 
* 
* Gets temperature and voltage as input parameters and invokes notifies 
* all observers that _value has been changed. 
* 
* _value is a number of LEDs that should be on. 
*/
void Solver::Run(ISubject& sender, float temp, float voltage, float K)
{
  // Use temp and voltage for more precise estimation of temperature. 
  temp = temp * K; 
  
  // Note that supported temperature range of the ADC: –40 to 125 °C. 
  std::int8_t minTemp = -40; 
  std::int8_t maxTemp = 125;
  std::uint8_t tempStep = (maxTemp - minTemp) / 4;      // By default there's only 4 LEDs.
  _value = 0;                                           // By default number of LEDs to be on is equal to 0. 
  
  // Get number of LEDs to be on. 
  if (temp < maxTemp && temp > minTemp)
  {
    for (std::uint8_t i = 0; i < 4; i++)                // By default there's only 4 LEDs. 
    {
      std::uint8_t temp_ref = minTemp + (tempStep * i); 
      
      if (temp >= temp_ref)
      {
        _value++; 
      }
    }
  }
  
  // Notify all observers. 
  for(auto& observer: _observers)
  {
    observer->OnUpdate(*this, _value);
  }
}