#include "rccregisters.hpp"
#include "gpiocregisters.hpp"
#include <iostream>

int Test(int value, int value1, int value2, int value3, int value4, int value5)
{
  std::cout << value << " "  << std::endl;
  return value ;
}

int main()
{  
  RCC::CR::HSEON::On::Set();
  while(!RCC::CR::HSERDY::Ready::IsSet())
  {
  }
 
  RCC::CFGR::SW::Hse::Set();
  
  while(!RCC::CFGR::SWS::Hse::IsSet())
  {
  }
  
  RCC::CR::HSION::Off::Set();
  
  //Подать тактирование на порт С
  //*reinterpret_cast<std::uint32_t*>(0x40023830) = 1U << 2U ; 
  volatile int t = 0;   
  RCC::AHB1ENR::GPIOCEN::Enable::Set();
  //Настроить PortC.5 на выход. Регистр PortC.MODER5, Адрес см. https://www.st.com/resource/en/datasheet/stm32f411re.pdf  стр 54
  // Описание регистра см https://www.st.com/resource/en/reference_manual/dm00119316-stm32f411xce-advanced-armbased-32bit-mcus-stmicroelectronics.pdf стр. 157
 // *reinterpret_cast<std::uint32_t* >(0x40020800) |= 1U << 10U;
  
  GPIOC::MODER::MODER5::Input::Set();
  
  //Вывести 1 в PortC.5. Регистр ODR м https://www.st.com/resource/en/reference_manual/dm00119316-stm32f411xce-advanced-armbased-32bit-mcus-stmicroelectronics.pdf стр. 159
  //*reinterpret_cast<std::uint32_t* >(0x40020814) |= 1U << 5U; 
  
  for(;;)
  {
    for (int i= 0; i < 1000000 ; i ++)
    {
    }
    
    GPIOC::ODR::ODR5::High::Set() ;
  
    for (int i= 0; i < 1000000 ; i ++)
    {
    }
    GPIOC::ODR::ODR5::Low::Set() ;
  }
  return 1 ;
}
