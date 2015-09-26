#include "Scheduler.h"
#include <TaskHelper.h>
#include <TaskHelperWithData.h>
#include <new.h>

//----------------------------------------------------------------------------------------------------
// Public
//----------------------------------------------------------------------------------------------------

bool Scheduler::addTask(Task * task, unsigned long int timer, bool reshot)
{
  return addTask(task, timer, reshot, false, false);
}

bool Scheduler::addTask(void (* func)(void), unsigned long timer, bool reshot)
{
  Task * task = new TaskHelper(func);
  return addTask(task, timer, reshot, true, false);
}

bool Scheduler::addTask(void (* func)(void *), void * data, unsigned long timer, bool reshot)
{
  Task * task = new TaskHelperWithData(func, data);
  return addTask(task, timer, reshot, false, true);
}

void Scheduler::scheduleTasks(void)
{
  for (unsigned char i = 0; i < MAX_TASKS; i++)
  {
    if (tasks[i].isUsed())
    {
      if (tasks[i].ready())
        tasks[i].run();
    }
  }
}


//----------------------------------------------------------------------------------------------------
// Private
//----------------------------------------------------------------------------------------------------

bool Scheduler::addTask(Task * task, unsigned long timer, bool reshot, bool isTaskHelper, bool isTaskHelperWithData)
{
  for (unsigned char i = 0; i < MAX_TASKS; i++)
  {
    if (tasks[i].isFree())
      return tasks[i].set(task, timer, reshot, isTaskHelper, isTaskHelperWithData);
  }

  return false;
}

void Scheduler::removeTaskPerIndex(unsigned long index)
{
  tasks[index].remove();
}
