#include "Repository.h"

bool Repository::add_task_to_repository(const Task& new_task)
{
    const std::vector<Task>& tasks_from_repository = this->tasks;

    for (const Task& task : tasks_from_repository)
        if (new_task.get_description() == task.get_description())
            return false;

    this->tasks.push_back(new_task);
    return true;

}

const std::vector<Task>& Repository::get_all_tasks_from_repository() const
{
    return this->tasks;
}
