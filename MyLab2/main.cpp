#include <iostream>

float operator""_F(float);
using tMyVar = float; 
tMyVar myVar = 40'000'000'000F; 

int main()
{
  std::cout << "myVar = " << myVar << std::endl; 
  std::cout << "myVar + 1.0f = " << myVar + 1.0f << std::endl; 
  
  return 0;
}
