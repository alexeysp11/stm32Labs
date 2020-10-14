#include <iostream>

using tMyVar = short int;
tMyVar myVar = 65535;

int main()
{
  std::cout << "myVar = " << myVar << std::endl;
  std::cout << static_cast<short>(myVar) << std::endl;

  return 0;
}
