/**
 * @file task_manager.h
 * @author Daniel (daniel@techcraftblog.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef _TASK_MANAGER_H_
#define _TASK_MANAGER_H_

#include "inttypes.h"

//has to be less than 255
#define MAX_QUEUE_TASKS 16
#define MAX_QUEUES 16


typedef enum{
  TM_OK,
  TM_FAIL
}TDef_TMStatus;

typedef TDef_TMStatus (*Tdef_QueueTask)(void); 
typedef uint32_t (*TDef_GetTick)(void);



typedef struct{
  uint8_t handle;
  uint16_t ms_period;
  uint32_t present_tasks;  
  Tdef_QueueTask tasks[MAX_QUEUE_TASKS];
}TDef_Queue;

extern TDef_Queue TMQueues[MAX_QUEUES];
extern uint8_t init_queues;
extern TDef_GetTick getTick;

TDef_TMStatus taskManagerInit(TDef_GetTick tick_f);
uint8_t queueCreate(uint16_t period);
uint8_t queueAddTask(uint8_t q_handle, Tdef_QueueTask task_f);
TDef_TMStatus queueRemoveTask(uint8_t q_handle, uint8_t task_handle);
TDef_TMStatus runQueueManager();
TDef_TMStatus queueRunAllTasks(uint8_t q_handle);



#endif