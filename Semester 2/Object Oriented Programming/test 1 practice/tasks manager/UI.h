#pragma once
#include "Controller.h"
class UI
{
private:
	Controller controller;

public:
	UI(Controller& _controller);

	void show_all_tasks() const;

	void show_sorted_tasks_with_less_priority(const int& priority) const;

	void start_program();
};

