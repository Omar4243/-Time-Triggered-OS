/**
 * @author Omar Megahed
 * @email omarmegahed741@gmail.com
 * @create date 2022-08-09 14:20:33
 * @modify date 2022-08-09 14:20:33
 * @desc OS.c
 */
/************************************************************
                       includes
************************************************************/
#include "OS.h"
#include "Macros.h"
#include "Std_Type.h"
#include "SysTick.h"
/************************************************************
                  static global variables
************************************************************/
static Task_t Task[MAX_TASKS_NUM];
/************************************************************
                function implementation
************************************************************/
void SCH_Init(uint8_t TickTime) // tick time in ms
{
  uint8_t i;
  for (i = 0; i < MAX_TASKS_NUM; i++)
  {
    Task[i].Func = NULL;
    Task[i].RunMe = 0;
  }
  // Timer Tick (ms) configuration
  SysTick_Interrupt_Init(TickTime);
}

void SCH_Start(void)
{
  // Enable timer To start
  SysTick_Start();
}

void SCH_AddTask(void (*Func_Name)(void), Tick_t Delay, Tick_t Period, uint8_t Priority)
{

  if (Priority < MAX_TASKS_NUM)
  {
    if (Func_Name != NULL)
    {
      Task[Priority].Func = Func_Name;
      Task[Priority].Delay_Ticks = Delay;
      Task[Priority].Period_Ticks = Period;
      Task[Priority].RunMe = 0;
    }
    else
    {
      /*ERROR PRIORTY*/
    }
  }
  else
  {
    /*NO EMPTY LOCATION*/
  }
}

void SCH_DelTask(void (*Func_Name)(void))
{
  uint8_t i = 0;
  // search for task name
  for (i = 0; i < MAX_TASKS_NUM; i++)
  {
    if (Task[i].Func == Func_Name)
    {
      // clear Task Function
      Task[i].Func = NULL;
      break;
    }
  }
}

void SCH_Update(void)
{
  uint8_t i = 0;
  for (i = 0; i < MAX_TASKS_NUM; i++) // loop for all tasks
  {
    if (Task[i].Func != NULL) // check task function is located or deleted
    {
      if (Task[i].Delay_Ticks > 0) // check task delay time
      {
        Task[i].Delay_Ticks--;
      }
      else if (Task[i].Delay_Ticks == 0) // check task delay time
      {
        Task[i].RunMe++;              // task is ready to execute
        if (Task[i].Period_Ticks > 0) // task periodicity check
        {
          Task[i].Delay_Ticks = Task[i].Period_Ticks - 1; // task will be ready again after period
        }
        else
        {
          /* one shot task*/
        }
      }
      else
      {
        /*ERORR*/
      }
    }
    else
    {
      /*Task deleted*/
    }
  }
}

void SCH_Dispatch(void)
{
  uint8_t i = 0;
  for (i = 0; i < MAX_TASKS_NUM; i++)
  {
    if ((Task[i].Func != NULL) && (Task[i].RunMe > 0))
    {
      (*Task[i].Func)();             // Execute task function
      Task[i].RunMe--;               // task status blocked
      if (Task[i].Period_Ticks == 0) // one shot task "execute once then deleted"
      {
        SCH_DelTask(Task[i].Func); // delete one shot task
      }
    }
  }
}
