#include "UI.h"
#include <iostream>
#include <sstream>
#include <regex>

UI::UI(Controller& _controller) : controller(_controller)
{
}

void UI::show_all_tasks() const
{
	std::vector<Task> tasks = this->controller.get_tasks();

	if (tasks.size() == 0){
		std::cout << "No tasks left in repository. Add some!\n";
		return;
		}

	std::cout << "The repository:\n";
	for (const Task& task : tasks)
		std::cout << task.to_string() << "\n";
}

void UI::show_sorted_tasks_with_less_priority(const int& priority) const
{
	std::vector<Task> sorted_tasks = this->controller.get_sorted_tasks_with_priority_less_than_given_one(priority);

	if (sorted_tasks.size() == 0) {
		std::cout << "No tasks left in sorted repository!\n";
		return;
	}

	std::cout << "The sorted repository:\n";
	for (const Task& task : sorted_tasks)
		std::cout << task.to_string() << "\n";
}

std::vector<std::string> split_command(const std::string& command, char separator)
{
	std::string argument;
	std::vector<std::string> arguments;
	std::istringstream argumentStream(command);

	bool single_argument = true;

	while (std::getline(argumentStream, argument, separator)) {
		arguments.push_back(argument);
		single_argument = false;
	}

	if (single_argument)
		arguments.push_back(command);

	return arguments;
}

void print_menu()
{
	std::cout << "\n> add,<description>,<duration>,<priority>\n";
	std::cout << "> show all\n";
	std::cout << "> display sorted,<priority>\n";
	std::cout << "> exit\n";
	std::cout << "\n> ";
}

void UI::start_program()
{
	std::string command;
	std::vector<std::string> arguments;

	std::cout << "Welcome to Task Manager!\n";

	while (true) {
		print_menu();

		std::getline(std::cin, command);
		arguments = split_command(command, ',');

		std::regex pattern("^[0-9]+$");

		if (arguments.size() == 1 && arguments[0] == "exit")
			break;

		else if (arguments.size() == 1 && arguments[0] == "show all")
			this->show_all_tasks();

		else if (arguments.size() == 4 && arguments[0] == "add") {
			if (!std::regex_match(arguments[2], pattern)) {
				std::cout << "The 3rd argument must be an integer!\n";
				continue;
			}

			if (!std::regex_match(arguments[3], pattern)) {
				std::cout << "The 4th argument must be an integer!\n";
				continue;
			}
			bool add_status;
			add_status = this->controller.add_task(Task{ arguments[1], std::stoi(arguments[2]), std::stoi(arguments[3]) });
		
			if (add_status == true)
				std::cout << "The task has been successfully added!\n";

			else
				std::cout << "The task has not been added!\n";
		}

		else if (arguments.size() == 2 && arguments[0] == "display sorted") {
			if (!std::regex_match(arguments[1], pattern)) {
				std::cout << "The second argument must be an integer!\n";
				continue;
			}
		
			this->show_sorted_tasks_with_less_priority(std::stoi(arguments[1]));
		}

		else
			std::cout << "Unknown command!\n";

	}

	std::cout << "\nThank you for using the application!\n";
}