// File Observers.hpp contains all interfaces used in Observer pattern. 

#ifndef _STM32LABS_OBSERVERS_H_
#define _STM32LABS_OBSERVERS_H_

#include <cstdint>

class IObserver;
class ISubject
{
public: 
  virtual void Subscribe(IObserver& observer) = 0;
  virtual void Unsubscribe(IObserver& observer) = 0;
}; 

class IObserver
{
public:
  virtual void OnUpdate(ISubject& sender, std::uint8_t value) = 0; 
}; 

class IObserverMeasurer 
{
public: 
  virtual void Run(ISubject& sender, float temp, float voltage, float K) = 0;
  virtual void OnUpdate(float temp, float voltage, float K) = 0; 
}; 

class ISubjectMeasurer 
{
public: 
  ISubjectMeasurer() = default; 
  virtual void Subscribe(IObserverMeasurer& observer) = 0; 
  virtual void Unsubscribe(IObserverMeasurer& observer) = 0;
}; 

class IMeasurer 
{
public: 
  virtual float GetValue() = 0; 
}; 

#endif