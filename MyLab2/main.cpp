#include <iostream>

using tMyVar = short unsigned int; 
tMyVar myVar = 32767; 

int main()
{
  //tMyVar* ptrMyVar = &myVar; 
  short* ptrMyVar = reinterpret_cast<short*>(&myVar);
  
  myVar++; 
  
  std::cout << "myVar = " << myVar << std::endl; 
  std::cout << "ptrMyVar = " << ptrMyVar << std::endl; 
  
return 0;
}
