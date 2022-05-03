#pragma once
#include <vector>
#include "Task.h"

class Repository
{
private:
	std::vector<Task> tasks;

public:
	bool add_task_to_repository(const Task& new_task);

	const std::vector<Task>& get_all_tasks_from_repository() const;

};
