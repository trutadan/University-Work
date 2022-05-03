#include "Controller.h"
#include <algorithm>

Controller::Controller(const Repository& _repository) : repository(_repository)
{
}

bool Controller::add_task(const Task& new_task)
{
    /*
    Add new task to the repository if there is not another one with the same name.
    Return: true if the task has been successfully added, false otherwise.
    */

    return this->repository.add_task_to_repository(new_task);
}

const std::vector<Task>& Controller::get_tasks() const
{
    return this->repository.get_all_tasks_from_repository();
}

std::vector<Task> Controller::get_sorted_tasks_with_priority_less_than_given_one(const int& priority) const
{
    /*
    Sort the repository in descending order, by duration. Given a priority as parameter, make a new vector which contains
    only the tasks which have priority less than the given one.
    Return: the sorted repository.
    */

    std::vector<Task> sorted_tasks = this->repository.get_all_tasks_from_repository();
    
    auto sort_method = [](const Task& first_task, const Task& second_task) {
        return first_task.get_duration() > second_task.get_duration();
    };

    std::sort(sorted_tasks.begin(), sorted_tasks.end(), sort_method);

    std::vector<Task> sorted_tasks_by_priority;

    for (const Task& task : sorted_tasks)
        if (task.get_priority() < priority)
            sorted_tasks_by_priority.push_back(task);

    return sorted_tasks_by_priority;
}
