# RtosWrapper_Report 

Для выполнения данной работы была использована [оболочка](https://github.com/lamer0k/RtosWrapper) к операционной системе реального времени [FreeRTOS](https://github.com/FreeRTOS/FreeRTOS). 

Все использованные ресурсы представлены в разделе [Использованная литература](#sources). 

## Содержание 

1. [Исходное задание](#requirements)
1. [Теоретический материал](#theory)
1. [Проектирование](#design)
1. [Написание кода](#coding)
1. [Использованная литература](#sources)

## Исходное задание <dev id="requirements"></dev>

В данной работе необходимо разобраться с [оболочкой](https://github.com/lamer0k/RtosWrapper) к [FreeRTOS](https://github.com/FreeRTOS/FreeRTOS) и научиться с помощью этой оболочки моргать светодиодами и одновременно отслеживать нажатие кнопки. 
На каждое нажатие кнопки нужно менять состояние определённого светодиода на противоположное (включить/выключить). 

## Теоретический материал <dev id="theory"></dev>

**Планирование выполнения задач** (англ. **Scheduling**) - это метод, который позволяет распределять выполнение задач между ресурсами компьютера и который управляется с помощью *планировщика* (или *диспетчера операционной системы*). 

*Планировщики* часто реализуются таким образом, чтобы задействовать все ресурсы компьютера (как при *балансировке нагрузки*). 
Концепция планирования позволяет имплементировать *многозадачность* компьютера с помощью одного центрального процессора.

Под **балансировкой нагрузки** (англ. **Load balancing**) понимают процесс распределения набора задач между ресурсами компьютера с целью обеспечения их максимально эффективного выполнения. 

Методы *балансировки нагрузки* позволяют оптимизировать время отклика для каждой задачи, избегая неравномерной перегрузки вычислительных узлов, когда другие вычислительные узлы остаются простаивающими.

**Поток** (англ. **Thread**) - это наименьшая последовательность программных инструкций, которые выполняются независимо и управляются *диспетчером операционной системы*. 

**Процесс** (англ. **Process**) - это часть компьютерной программы, исполняемой несколькими *потоками*. 

Разница между *программой*, *процессом* и *потоком*: 

![ProgramProcessThread](https://upload.wikimedia.org/wikipedia/commons/thumb/2/25/Concepts-_Program_vs._Process_vs._Thread.jpg/400px-Concepts-_Program_vs._Process_vs._Thread.jpg)

Реализация *потоков* и *процессов* в разных операционных системах различается, но в большинстве случаев поток является компонентом процесса.

**Многозадачность** (англ. **Multitasking**) - это одновременное выполнение нескольких задач или процессов в течение определенного периода времени. 
Новые задачи могут прерывать уже начатые до их завершения, а не ждать их завершения. 
В результате компьютер выполняет сегменты множества задач с чередованием, в то время как задачи совместно используют общие ресурсы обработки, такие как центральные процессоры и основная память. 

Паттерны планирования: 
1. **First come, first served** (**FCFS**): реализация похожа на реализацию *очереди* (англ. *Queue*), действующей по принципу *"первый зашёл, первый вышел"* (англ. *First in, first out*) т.е. раньше всего будет выполняться та задача, которая раньше всего была создана; 
1. **Shortest Job First** (**SJF**): выполняться будет та задача, которая требует меньше всего времени на выполнение. 
*Преимуществом* такого алгоритма является его простота реализации. 
А очевидным его *недостатком* является следующее: если мелких задач будет много, и они будут постоянно появляться, то более долгие по времени (а иногда даже более важные) задачи будут постоянно откладываться, и тогда система в лучшем случае подвиснет, а в худшем приведёт к сбою. 
1. **Shortest remaining time first**: алгоритм, похожий на расширенную версию *Shortest Job First*; в этом алгоритме планирования для выполнения выбирается процесс с наименьшим количеством времени, оставшимся до завершения. 
Поскольку текущий выполняющийся процесс - это процесс с наименьшим оставшимся временем по определению, и поскольку это время должно только уменьшаться по мере выполнения, процессы всегда будут выполняться до тех пор, пока они не завершатся или не будет добавлен новый процесс, требующий меньшего количества времени. 
1. **Earliest deadline first** (**EDF**) также известен как **least time to go**: алгоритм динамического планирования, используемый в *операционных системах реального времени* для помещения процессов в приоритетную очередь. 
Каждый раз, когда происходит событие планирования (нарпимер, завершение задачи или отмена новой задачи), в очереди будет производиться поиск процесса, ближайшего к *дэдлайну* - именно он будет следующим по расписанию для выполнения.
1. **Fixed priority pre-emptive scheduling**; 
1. **Round-robin scheduling**; 
1. **Multilevel queue scheduling**. 

**Вычисления в реальном времени** (англ. **Real-time computing**, **RTC**) - это термин в компьютерной науке для аппаратных и программных систем, подверженных ограничениям в реальном времени (например, от момента возникновения события до момента реакции системы). 
Программы, работающие в реальном времени, должны гарантировать ответ в установленные сроки, часто называемые **дэдлайнами** (англ. **Deadline**). 

**Операционная система реального времени** (англ. **Real Time Operating System**, **RTOS**) - это операционная система, которая предназначена для обслуживания *real time*-приложений, которые обрабатывают данные по мере их поступления, обычно без задержек в буфере (в области физической памяти, которая используется для временного хранения данных во время их перемещения из одного места в другое). 
Требования ко времени обработки (включая любую задержку ОС) измеряются десятыми долями секунды или более короткими интервалами времени. 
*Система реального времени* очень сильно привязана ко времени и имеет четко определенные фиксированные временные ограничения, поэтому обработка должна выполняться в рамках определенных ограничений, иначе система выйдет из строя. 

На рисунке снизу представлена общие компоненты, из которых состоит *ОСРВ*: 

![RTOS-System](https://engineersgarag.wpengine.com/wp-content/uploads/2019/07/A-Figure-Showing-Common-Services-Offered-A-RTOS-System.jpg)

## Проектирование <dev id="design"></dev>

Вся реализация, которая нужна для выполнения данной работы, уже есть в проекте, который был выдан изначально, просто нужно было её найти, а не придумывать свою. 

Верхний уровень приложения (то, с чем непосредственно я работал) состоит из следующих модулей: 
- **Task** - в этом приложении две задачи: 
    1. моргание светодиодами 2 и 3 с периодом (период моргания светодиодами равен 1000 мс); 
    2. отслеживание нажатие кнопки и переключение состояние светодиода 1 (период проверки состояния кнопки равен 100 мс). 
- **Events**: создавались экземпляры класса `OsWrapper::Event` - `buttonEvent` и `ledsEvent`, т.е. для каждой задачи используется своё событие со своим определённым интервалом срабатывания;
- **Tasks**: подразумеваются классы `HandleBtnTask` и `ToggleLedsTask`; 
- **Leds**: в файле `leds.hpp` уже находилось определение интерфейса (абстрактной структуры) `ILed` и класса `Led` для всех светодиодов; 
- **Button**: определение для кнопки (класс `Button`) находилось в файле `userbutton.hpp`; 
- **Pin**: реализация пинов производится с помощью структуры `Pin` и находится в файле `pin.hpp`;
- **Port**: реализация портов производится с помощью структуры `Port` и находится в файле `port.hpp`. 

Прорисовка архитектуры не производилась ввиду того, что существуют модули данной программы, с которыми все вышеприведённые классы взаимодействуют и которые находятся на более низких уровнях абстракции. 
Поэтому я не берусь утверждать, какие точно существуют взаимосвязи между всеми классами программы. 

## Написание кода <dev id="coding"></dev>

В данном разделе представлен не весь код, а только "верхний" уровень приложения, с которым непосредственно проводилась работа. 

В ходе работы мне пришлось более плотно изучить, как устроена **оболочка** для **FreeRTOS**, в некоторые места исходного кода были добавлены комментарии для облегчения работы. 

Например, метод `Rtos::CreateThread()` принимает строковое значение названия задачи (точнее, `char *` - указатель на массив символов).
Казалось бы, зачем здесь нужно строковое значение в качестве аргумента?  
В результате более углублённого изучения кода, было выяснено, что это необходимо для облегчения работы с отладчиком, и в комментарии к методу `Rtos::CreateThread()` было добавлено данное уточнение. 

Итак, объявляем задачи в файле `main.cpp`. 
Для этого инициализируем события и задачи для для обработки кнопки и для моргания светодиодами:  
```C++
// An event for button handling every 100 ms, mask equal to 1. 
OsWrapper::Event buttonEvent{100ms, 1};

// An event for toggling LEDs 2 and 3 every 1000 ms, mask equal to 1. 
OsWrapper::Event ledsEvent{1000ms, 1};

// A task for handling a button. 
HandleBtnTask btnTask(buttonEvent, UserButton::GetInstance(), LedsModeFirst::GetInstance());

// A task for toggling LEDs. 
ToggleLedsTask ledsTask(ledsEvent, LedsController::GetInstance());

/*
* In the main function create threads and start RTOS. 
*/ 
int main()
{
  // Create threads.
  using namespace OsWrapper;
  Rtos::CreateThread(btnTask, "btnTask", ThreadPriority::lowest);
  Rtos::CreateThread(ledsTask, "ledsTask");
  
  // Start RTOS. 
  Rtos::Start();

  return 0;
}
```

### Работа с задачей для переключения светодиодов

Файл `ToggleLedsTask.hpp` содержит класс декларирование класса `ToggleLedsTask`:
```C++
/*
* Toggles LEDs 2 and 3. 
* 
* Constructor of `ToggleLedsTask` gets created event for LEDs toggling and 
* a reference to the instance of `LedsController` as parameters. 
*/ 
class ToggleLedsTask : public OsWrapper::Thread<static_cast<std::size_t>(OsWrapper::StackDepth::minimal)>
{
public:
  virtual void Execute() override;

  ToggleLedsTask(OsWrapper::Event& event, LedsController& controller) : event(event), ledsCntr(controller)
  {
  }
  
private:
  OsWrapper::Event& event;
  LedsController& ledsCntr;
};
```

Как видно, класс `ToggleLedsTask` в качестве одного из параметров в конструкторе принимает ссылку на сущность класса `LedsController`. 
Это даёт возможность при реализации метода `Execute()` обращаться к методу `Update()` класса `LedsController`, т.е. осуществлять выполнение одного из режимов работы светодиодов (в данном случае режима `LedsModeInsideOutside`, выполняющего переключение светодиодов 2 и 3). 

Реализация метода `Execute()` класса `ToggleLedsTask` представлена в файле `ToggleLedsTask.cpp`:
```C++
/*
* Summary: executes a task `ToggleLedsTask`.
* Sleep some amount of time until an event occurs (when desired delay has 
* passed and mask is equal to 0) and then toggle required LEDs. 
* 
* Parameters: No. 
*/ 
void ToggleLedsTask::Execute()
{
  // Set mode `LedsModeInsideOutside` that implements toggling LEDs 2 and 3. 
  ledsCntr.SetMode(4U);         
  
  for(;;)
  {
    // Wait the end of event (mask will be equal to 0) and do nothing. 
    if (event.Wait() != 0); 
    
    /* Invoke `Update()` method of an instance of `LedsController` class
    that was passed to the constructor of this class as a parameter. */ 
    ledsCntr.Update();
  }
}
```

Декларация и реализация класса `LedsController` представлены в файле `ledscontroller.hpp`: 
```C++
/*
* This is kind of base class for implementing different modes of LEDs. 
*/ 
class LedsController : public Singleton<LedsController>
{
public:
  /*
  * Summary: executes required mode of LEDs. 
  * 
  * Parameters: [in] value - some value that is not used in the method. 
  */ 
  inline void Update(std::uint8_t value = 0)
  {
    modes[currentMode].get().Do(value);
  }
  
  /*
  * Changes a mode of LEDs. 
  */ 
  inline void NextMode()
  {
    currentMode++;
    
    if (currentMode >= modes.size())
    {
      currentMode = 0U;
    }
    
    modes[currentMode].get().Reset();
  }
  
  /* 
  * This function is used for explicit setting execution mode of LEDs. 
  */ 
  inline void SetMode(std::size_t mode)
  {
    currentMode = mode; 
  }
  
  friend class Singleton<LedsController>;
  
private:
  LedsController() = default;        
  std::size_t currentMode = 0U;   // By default a mode index is equal to 0, i.e. implement a tree.
  using tModesArray = std::array<std::reference_wrapper<LedsMode>, 7U>;    
  tModesArray modes = { 
                        LedsModeTree::GetInstance(),
                        LedsModeChess::GetInstance(),
                        LedsModeAll::GetInstance(),
                        LedsModeFirstPair::GetInstance(),
                        LedsModeInsideOutside::GetInstance(),
                        LedsModeAdc::GetInstance(), 
                        LedsModeFirst::GetInstance()
                      }; 
};
```

Определение класса `LedsModeInsideOutside` выполнено в файле `ledsmodes.hpp`: 
```C++
/*
* Toggles LEDs 2 and 3, inherits classes `LedsMode` and `Singleton`.
*/ 
class LedsModeInsideOutside : public LedsMode, public Singleton<LedsModeInsideOutside>
{
  friend class Singleton<LedsModeInsideOutside>;
  public:
    /*
    * Summary: toggles LEDs 2 and 3.
    * 
    * Parameters:   [in] value - some value (it is not used in the method). 
    * 
    * Remarks: gets an instance of `LedsDriver` class toggles LEDs 2 and 3. 
    */ 
    virtual void Do(std::uint8_t value) override
    {
      // An instance of `LedsDriver` class. 
      LedsDriver& driver = LedsDriver::GetInstance();
      
      driver.GetLed(LedNum::led2).Toggle();     // Toggle LED 2. 
      driver.GetLed(LedNum::led3).Toggle();     // Toggle LED 3. 
    }
   private:
    LedsModeInsideOutside() = default;  
};
```

### Работа с задачей для обработки кнопки

Файл `HandleBtnTask.hpp` содержит декларирование класса `HandleBtnTask`: 
```C++
/*
* Overrides `Execute()` method and inherits `Thread` class (file "thread.hpp"). 
*
* Size of a stack is minimal (128 bytes). 
*/
class HandleBtnTask : public OsWrapper::Thread<static_cast<std::size_t>(OsWrapper::StackDepth::minimal)>
{
  friend class Singleton<LedsModeFirst>;
public:
  virtual void Execute() override;
  HandleBtnTask(OsWrapper::Event& event, UserButton& button, 
                LedsModeFirst& mode) : event(event), button(button), ledsMode(mode)
  {
  }
private:
  OsWrapper::Event& event;
  UserButton& button;
  LedsModeFirst& ledsMode; 
};
```

Данный класс должен определять нажате кнопки, что реализовано с помощью метода `Execute()` в файле `HandleBtnTask.cpp`: 
```C++
/*
* Summary: in an infinite `while` loop every 100 ms check if a button is pressed. 
* If a button was pressed, just invoke `Do()` method of an instance of 
* `LedsModeFirst` class and toggle required LED. 
* 
* TODO: try to toggle LED by notifying an instance of `OsWrapper::Event` 
* about that a button was pressed. 
*/
void HandleBtnTask::Execute()
{
  using namespace OsWrapper; 
  while(true) 
  {
    if (button.IsPressed())
    {
      /* Invoke `Do()` method of an instance of `LedsModeFirst` class
      that was passed to the constructor of this class as a parameter,
      and toggle LED 1. */ 
      ledsMode.Do(); 
    }

    /* Invoke `OsWrapper::IThread::Sleep()` that makes a delay that is 
    equal to a value of timeout between events. */
    Sleep( std::chrono::milliseconds( event.GetTimeout() ) );
  }
}
```

В данном примере вызов переключения состояния светодиода 1 производился напрямую через обращение к методу класса. 
Хотя, насколько я понял, это можно сделать черз оповещение с помощью метода `event.Signal()`, но я не смог разобраться, как его можно использовать для этих целей. 

Для данной задачи в качестве одного из параметров конструктора класса `HandleBtnTask` передавалась ссылка на сущность класса `LedsModeFirst`. 
Сам класс `LedsModeFirst` определён следующим образом (файл `ledsmodes.hpp`): 
```C++
/*
* Allows to toggle only first LED. 
*/
class LedsModeFirst : public LedsMode, public Singleton<LedsModeFirst>
{
  friend class Singleton<LedsModeFirst>;
  public:
    /*
    * Summary: toggles only LED 1.
    * 
    * Parameters:   [in] value - some value (it is not used in the method). 
    * 
    * Remarks: gets an instance of `LedsDriver` class toggles LED 1. 
    */ 
    virtual void Do(std::uint8_t value = 0U) override
    {
      // An instance of `LedsDriver` class. 
      LedsDriver& driver = LedsDriver::GetInstance();
      
      driver.GetLed(LedNum::led1).Toggle();     // Toggle LED 1.         
    }
    private:
    LedsModeFirst() = default;  
};
```

Ещё очень интересный момент, что в данном приложении реализуется паттерн **Singleton**, который накладывает определённые ограничения на создание сущностей одного класса (в программе может существовать максимум только один объект каждого класса).

Честно сказать, не совсем понимаю в чём преимущество использования такого паттерна, но зато я знаю, как можно было обойти в данной работе ограничения, которые он накладывал. 
Так, переключение состояния светодиодов, по сути, осуществляется с двух сторон, и у меня изначально было желание использовать `LedsController` в обоих случаях. 
Но потом в процессе дебаггинга я увидел, что создаётся один и тот же объект (а именно, при пошаговой отладке и при нажатии кнопки программа заходила в класс, который использовался для переключения светодиодов 1 и 2, а не светодиода 1). 

Поэтому было решено обращаться к классу `LedsModeFirst` напрямую из класса `HandleBtnTask`, а не через `LedsController`. 

## Использованная литература <dev id="sources"></dev>

1. https://en.wikipedia.org/wiki/Scheduling_(computing)
1. https://en.wikipedia.org/wiki/Load_balancing_(computing)
1. https://en.wikipedia.org/wiki/Thread_(computing)
1. https://en.wikipedia.org/wiki/Shortest_job_next
1. https://en.wikipedia.org/wiki/Computer_multitasking
1. https://en.wikipedia.org/wiki/Real-time_operating_system
1. https://en.wikipedia.org/wiki/Data_buffer
