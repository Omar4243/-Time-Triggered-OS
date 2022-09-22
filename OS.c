/*Headers*/
#include "OS.h"
#include "Macros.h"
#include "Std_Type.h"
#include "SysTick.h"
/*Task info structs*/
static Task_t Task[MAX_TASKS_NUM];
/****************************************************************************
*                        Scheduler initialize                               *
*****************************************************************************/
void SCH_Init(uint8 TickTime)//tick time in ms
{
    uint8 i;
    for (i = 0; i < MAX_TASKS_NUM; i++)
    {
      Task[i].Func = NULL;
      Task[i].RunMe=0;
    }
  // Timer Tick (ms) configuration
	SysTick_Interrupt_Init(TickTime);
}
/****************************************************************************
*                        Scheduler start                                    *
*****************************************************************************/
void SCH_Start(void)
{
  // Enable timer To start
	 SysTick_Start();
}
/****************************************************************************
*                        Scheduler Add Task                                 *
*****************************************************************************/
void SCH_AddTask(void (*Func_Name)(void), Tick_t Delay, Tick_t Period, uint8 Priority)
{
 
   if (Priority < MAX_TASKS_NUM)
      {
          if (Func_Name != NULL)
             {
               Task[Priority].Func = Func_Name;
               Task[Priority].Delay_Ticks = Delay;
               Task[Priority].Period_Ticks = Period;
               Task[Priority].RunMe=0;
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
/****************************************************************************
*                        Scheduler Delete Task                              *
*****************************************************************************/
void SCH_DelTask(void (*Func_Name)(void))
{
  uint8 i = 0;
  //search for task name 
  for (i = 0; i < MAX_TASKS_NUM; i++)
  {
      if (Task[i].Func == Func_Name)
         {
           //clear Task Function 
           Task[i].Func = NULL;
           break;
         }
  }
}
/****************************************************************************
*                        Scheduler Update  (ISR)                             *
*****************************************************************************/
void SCH_Update(void)
{
  uint8 i = 0;
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
              Task[i].RunMe ++;// task is ready to execute
              if (Task[i].Period_Ticks > 0) // task periodicity check
              {
                Task[i].Delay_Ticks = Task[i].Period_Ticks-1; // task will be ready again after period
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
/****************************************************************************
*                           Scheduler Dispatch                              *
*****************************************************************************/
void SCH_Dispatch(void)
{
  uint8 i = 0;
  for (i = 0; i < MAX_TASKS_NUM; i++)
  {
      if ((Task[i].Func != NULL) && (Task[i].RunMe >0))
      {
		  	  (*Task[i].Func)();//Execute task function
          Task[i].RunMe --;//task status blocked
          if (Task[i].Period_Ticks == 0)//one shot task "execute once then deleted"
          {
            SCH_DelTask(Task[i].Func);//delete one shot task
          }  
      }
  }  
}
