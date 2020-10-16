#include <iostream>

double myVar = 40'000'000'000.0F; 

int main()
{
  myVar += 1.0f;
  //static_cast<double>(myVar)
  
  std::cout << "myVar = " << myVar << std::endl; 
  
  return 0;
}
