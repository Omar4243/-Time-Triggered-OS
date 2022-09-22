/**
 * @author Omar Megahed
 * @email omarmegahed741@gmail.com
 * @create date 2022-08-09 14:20:33
 * @modify date 2022-08-09 14:20:33
 * @desc OS.h
 */
#ifndef _OS_H_
#define _OS_H_
/************************************************************
                        includes
************************************************************/
#include "Std_Type.h"
/************************************************************
                         defines
************************************************************/
#define MAX_TASKS_NUM (5U)
#define NULL ((void *)(0u))
/************************************************************
                        type defines
************************************************************/
typedef struct
{
    void (*Func)(void);
    uint8_t Period_Ticks;
    uint8_t Delay_Ticks;
    uint8_t RunMe;
} Task_t;

typedef uint8_t Tick_t;
/************************************************************
                  functions prototype
************************************************************/
/**
 * @brief scheduler init
 *
 * @param TickTime
 */
void SCH_Init(uint8_t TickTime);
/**
 * @brief scheduling tasks
 *
 */
void SCH_Update(void);
/**
 * @brief Dispatch tasks
 *
 */
void SCH_Dispatch(void);
/**
 * @brief
 *
 * @param Func_Name  task name
 * @param Delay delay tick from system start
 * @param Period periodicity of task
 * @param priority priority of task
 */
void SCH_AddTask(void (*Func_Name)(void), Tick_t Delay, Tick_t Period, uint8_t priority);
/**
 * @brief delete task
 *
 * @param Func_Name
 */
void SCH_DelTask(void (*Func_Name)(void));
/**
 * @brief enable tick timer interrut "scheduler start"
 *
 */
void SCH_Start(void);
#endif
