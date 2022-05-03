#pragma once
#include "Repository.h"
class Controller
{
private:
	Repository repository;

public:
	Controller(const Repository& _repository);

	bool add_task(const Task& new_task);

	const std::vector<Task>& get_tasks() const;

	std::vector<Task> get_sorted_tasks_with_priority_less_than_given_one(const int& priority) const;
};

