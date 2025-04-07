/**
 * @file task_manager.c
 * @author Daniel (daniel@techcraftblog.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "task_manager.h"

TDef_Queue TMQueues[MAX_QUEUES];
uint8_t init_queues = 0;
TDef_GetTick getTick;


TDef_TMStatus taskManagerInit(TDef_GetTick tick_f){
  if(tick_f == 0)TM_FAIL;

  getTick = tick_f;

  return TM_OK;
}



uint8_t queueCreate(uint16_t period){
  uint8_t handle = 0;
  if(init_queues >= MAX_QUEUES)return TM_FAIL;

  handle = init_queues;
  TMQueues[handle].handle = handle;
  TMQueues[handle].ms_period = period;

  init_queues++;
  return handle;
}


uint8_t queueAddTask(uint8_t q_handle, Tdef_QueueTask task_f){
  uint8_t task_free_idx = 0xff;
  uint8_t idx = 0;
  while(idx < MAX_QUEUE_TASKS){
    if(!(TMQueues[q_handle].present_tasks & (1<<idx))){
      task_free_idx = 0;
      break;
    }
    idx++;
  }

  if(task_free_idx == 0xff)return TM_FAIL;

  TMQueues[q_handle].present_tasks |= (1<<idx);
  TMQueues[q_handle].tasks[idx] = task_f;

  return idx;
}


TDef_TMStatus queueRemoveTask(uint8_t q_handle, uint8_t task_handle){
  if(TMQueues[q_handle].present_tasks & (1<<task_handle)){
    TMQueues[q_handle].present_tasks &= ~(1<<task_handle);
    return TM_OK;
  }

  return TM_FAIL;
}


TDef_TMStatus runQueueManager(){
  uint32_t tick; 
  
  if(init_queues == 0)return TM_FAIL;
  
  tick = getTick();

  for(uint8_t q_handle=0; q_handle < init_queues; q_handle++){
    if(tick % TMQueues[q_handle].ms_period == 0){
      queueRunAllTasks(q_handle);
    }
  }

  return TM_OK;
}


TDef_TMStatus queueRunAllTasks(uint8_t q_handle){
  uint8_t task_idx = 0;
  TDef_TMStatus ret = TM_FAIL;

  while(task_idx < MAX_QUEUE_TASKS){
    if(TMQueues[q_handle].present_tasks & (1<<task_idx)){
      ret |= TMQueues[q_handle].tasks[task_idx]();
    }
    task_idx++;
  }

  return ret;
}