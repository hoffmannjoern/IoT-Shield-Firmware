#ifndef SCHEDULER_H
	#define SCHEDULER_H

#include <Task.h>
#include <TaskControlBlock.h>

/**
 * @brief The Scheduler class provides basic scheduling capabilities. Simply add task objects to it with a timer and it
 * @brief will call its update-function after timer is zero. It is also possible to periodically call this function.
 * @param MAX_TASKS Maximum number of tasks, cause we hardcode this for simplicity.
 * @author Marc Vester (XaserLE)
 * @author Jörn Hoffmann (jhoffmann)
 */
class Scheduler
{
	public:
		/**
		 * @brief Adds a task to the scheduler.
		 * @param task Pointer to the task object that should be executed.
		 * @param timer task will be executed after timer milliseconds.
		 * @param reshot If true, func will be executed over and over every timer milliseconds.
		 * @return True if task was added, false if not (cause there was no space for another task).
		 */
		bool addTask(Task * task, unsigned long timer, bool reshot = true);

		/**
		 * @brief Adds a task to the scheduler.
		 * @param func Pointer to the function that should be executed.
		 * @param timer task will be executed after timer milliseconds.
		 * @param reshot If true, func will be executed over and over every timer milliseconds.
		 * @return True if func was added, false if not (cause there was no space for another task).
		 */
		bool addTask(void (* func)(void), unsigned long timer, bool reshot = true);

		/**
		 * @brief Adds a task to the scheduler.
		 * @param func Pointer to the function that should be executed.
		 * @param data The data the function will be called with.
		 * @param timer task will be executed after timer milliseconds.
		 * @param reshot If true, func will be executed over and over every timer milliseconds.
		 * @return True if func was added, false if not (cause there was no space for another task).
		 */
		bool addTask(void (* func)(void *), void * data, unsigned long timer, bool reshot = true);

	    /**
	     * @brief Tells us if a task was already added to the scheduler.
	     * @param task Pointer to the task object that should be executed. Valid types: Task *, void (* func)(void), void (* func)(void *).
	     * @return True if task is already in the scheduling list, false otherwise.
	     */
	    template<typename T>
	    bool taskExists(T task) const;

		/**
		 * @brief Removes a task from the scheduler.
		 * @param task Pointer to the task object that should be removed. Valid types: Task *, void (* func)(void), void (* func)(void *).
		 */
		template<typename T>
		void removeTask(T task);
		
		/**
		 * @brief This is the main function to schedule all tasks. Should be called every frame in the main loop.
		 */
		void scheduleTasks(void);
		
	private:
		/**
		 * @brief Adds a task to the scheduler. This function is used internally.
		 * @param task Pointer to the task object that should be executed.
		 * @param timer task will be executed after timer milliseconds.
		 * @param reshot If true, func will be executed over and over every timer milliseconds.
		 * @param isTaskHelper If true, this task was generated by the scheduler through the addTask()-functions with function pointers. The TaskControlBlock will take ownership of this.
		 * @param isTaskHelperWithData If true, this task was generated by the scheduler through the addTask()-functions with function pointers. The TaskControlBlock will take ownership of this.
		 * @return True if task was added, false if not (cause there was no space for another task).
		 */
	    bool addTask(Task * task, unsigned long timer, bool reshot, bool isTaskHelper, bool isTaskHelperWithData);

	    /**
	     * @brief Internal function that removes a task given by an index (faster than searching for the function pointer).
	     * @param index The index for the task. Valid values: [0 : MAX_TASKS-1].
	     */
	    void removeTaskPerIndex(unsigned long int index);

	    /**
	     * @brief Gives the index of a task if its in the scheduling list.
		 * @param task Pointer to the task object of which we want the index. Valid types: Task *, void (* func)(void), void (* func)(void *).
	     * @return The index of the task in the scheduler list [0 : MAX_TASKS-1]. -1 if task is not present.
	     */
	    template<typename T>
		char indexOf(T task) const;

		// Maximum number of tasks.
		static char const MAX_TASKS = 20;
		// Array with the tasks to schedule.
		TaskControlBlock tasks[MAX_TASKS];
};

#endif //SCHEDULER_H
