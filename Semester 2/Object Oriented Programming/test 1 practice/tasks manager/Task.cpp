#include "Task.h"

Task::Task(const std::string& _description, const int& _duration, const int& _priority) : description(_description), duration(_duration), priority(_priority)
{
}

const std::string& Task::get_description() const
{
	return this->description;
}

const int& Task::get_duration() const
{
	return this->duration;
}

const int& Task::get_priority() const
{
	return this->priority;
}

std::string Task::to_string() const
{
	std::string task_string;
	task_string = this->description + " | " + std::to_string(this->duration) + " | " + std::to_string(this->priority);

	return task_string;
}
