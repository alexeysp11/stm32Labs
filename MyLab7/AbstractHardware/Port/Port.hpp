#pragma once

#include <cstdint>
#include <cassert>

class IPortSet
{
public:
  virtual void Toggle(std::uint8_t num) = 0;
};

class IPortGet
{
public:
  virtual bool IsSet() = 0;
};

template <typename Reg>
class Port: public IPortSet, public IPortGet
{
public:
  void Toggle(std::uint8_t num) override
  {
     assert (num < 16);
     Reg::ODR::Toggle(1 <<num);
   }

  bool IsSet() override
  {
     return Reg::IDR::Get();
  }
};