#ifndef OS_H
#define OS_H
/*Headers*/
#include "Std_Type.h"
/************System TASK Numbers"User Defined"************/
#define MAX_TASKS_NUM (5U)
/*********************************************************/
//null pointer
#define NULL (void*)(0u)
/*Typedef Enums*/
//Task info type
typedef struct 
{
 void (*Func)(void);
 uint8     Period_Ticks;
 uint8     Delay_Ticks ;
 uint8     RunMe;
}Task_t;
//Tick type
typedef uint8 Tick_t;

/*Function Prototype*/
void SCH_Init(uint8 TickTime); //Tick Time in ms
void SCH_Update(void);
void SCH_Dispatch(void);
void SCH_AddTask(void(*Func_Name)(void),Tick_t Delay,Tick_t Period,uint8 priority);
void SCH_DelTask(void(*Func_Name)(void));
void SCH_Start(void);
#endif
