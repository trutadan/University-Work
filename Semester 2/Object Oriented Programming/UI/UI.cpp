#include "UI.h"
#include "../Functions/Exceptions.h"
#include "../Functions/Validator.h"
#include <iostream>

UI::UI(Controller& _controller) : controller(_controller)
{
}

void display_administrator_menu()
{
	std::cout << "\n> add <title>|<description>|<date>|<time>|<number of people>|<link>\n";
	std::cout << "> delete <title>\n";
	std::cout << "> update <title>|<new description>|<new date>|<new time>|<new number of people>|<new link>\n";
	std::cout << "> display\n";
	std::cout << "> exit\n\n";
	std::cout << "admin> ";
}

void display_user_menu()
{
	std::cout << "\n> mylist\n";
	std::cout << "> delete <title>\n";
	std::cout << "> display <month>\n";
	std::cout << "> exit\n\n";
	std::cout << "user> ";
}

void display_list_user_menu()
{
	std::cout << "\n\n> add\n";
	std::cout << "> next\n";
	std::cout << "> exit\n\n";
	std::cout << "user> ";
}

void UI::display_all_events_from_repository()
{
	if (this->controller.get_repository_length() == 0) {
		throw RepositoryError("There are no events in the database. Add some.");
	}

	if (this->controller.get_repository_type() != "inmemory" && this->controller.get_repository_type().substr(this->controller.get_repository_type().size() - 4) != ".sql") {
		this->controller.open_repository_file();
		return;
	}

	std::vector<Event> list_of_events = this->controller.get_all_events_from_repository();
	int events_list_length = this->controller.get_repository_length();
	this->controller.sort_events_by_date(list_of_events);

	std::cout << "title | description | date | hour | number of people | link\n";
	std::cout << "-----------------------------------------------------------\n";

	for (const Event& event: list_of_events)
		std::cout << event << std::endl;
}

void UI::display_all_events_from_list()
{
	if (this->controller.get_list_length() == 0) {
		throw ListError("There are no events in the list. Add some.");
	}

	if (this->controller.get_list_type() != "inmemory" && this->controller.get_list_type().substr(this->controller.get_list_type().size() - 4) != ".sql") {
		this->controller.open_list_file();
		return;
	}

	std::vector<Event> list_of_events = this->controller.get_all_events_from_list();
	this->controller.sort_events_by_date(list_of_events);

	std::cout << "title | description | date | hour | number of people | link\n";
	std::cout << "-----------------------------------------------------------\n";

	for (const Event& event : list_of_events)
		std::cout << event << std::endl;
}

void UI::ask_admin_for_new_file()
{
	std::cout << "Enter the type of the file in which you want to save the repository(inmemory/txt/csv/html/sql):" << std::endl;
	std::string file_type;

	while (true) {
		try {
			std::cout << "> ";
			std::getline(std::cin, file_type);
			this->controller.change_admin_repository_type(file_type);
			return;
		}

		catch (FileError& error_message) {
			std::cout << error_message.what() << std::endl;
		}
	}
}

void UI::ask_user_for_new_file()
{
	std::cout << "Enter the type of the file in which you want to save the events list(inmemory/txt/csv/html/sql):" << std::endl;
	std::string file_name;

	while (true) {
		try {
			std::cout << "> ";
			std::getline(std::cin, file_name);
			this->controller.change_user_repository_type(file_name);
			return;
		}

		catch (FileError& error_message) {
			std::cout << error_message.what() << std::endl;
		}
	}
}

void UI::start_program()
{
	std::cout << "Welcome to 'Life after School' program!\n";
	std::string mode;

	bool repository_type_chosen = false, list_type_chosen = false;

	while (1) {
		std::cout << "\n'admin', 'user', 'exit'? \n";

		std::cout << "> ";
		std::getline(std::cin, mode);

		std::string command;

		if (strcasecmp(mode, "admin")) {
			if (!repository_type_chosen) {
				ask_admin_for_new_file();
				repository_type_chosen = true;
			}

			display_administrator_menu();

			while (std::getline(std::cin, command)) {
				std::stringstream parser(command);
				std::string argument;
				parser >> argument;

				if (strcasecmp(argument, "add")) {
					Event event;

					try {
						parser >> event;
						this->controller.add_event_to_repository(event.get_title(), event.get_description(), event.get_datetime(), event.get_number_of_people(), event.get_link());
						std::cout << "Event has been successfully added.\n";
					}

					catch (ValueError& error_message) {
						std::cout << error_message.what() << std::endl;
					}

					catch (RepositoryError& error_message) {
						std::cout << error_message.what() << std::endl;
					}

					catch (FileError& error_message) {
						std::cout << error_message.what() << std::endl;
					}
				}

				else if (strcasecmp(argument, "delete")) {
					std::string title;
					parser >> argument;
					title = argument;

					while (parser >> argument)
						title += " " + argument;

					try {
						this->controller.remove_event_from_repository(title);
						std::cout << "Event has been successfully deleted.\n";
					}

					catch (ValueError& error_message) {
						std::cout << error_message.what() << std::endl;
					}

					catch (RepositoryError& error_message) {
						std::cout << error_message.what() << std::endl;
					}

					catch (FileError& error_message) {
						std::cout << error_message.what() << std::endl;
					}

				}

				else if (strcasecmp(argument, "update")) {
					Event event;

					try {
						parser >> event;
						this->controller.update_event_from_repository(event.get_title(), event.get_description(), event.get_datetime(), event.get_number_of_people(), event.get_link());
						std::cout << "Event has been successfully updated.\n";
					}

					catch (ValueError& error_message) {
						std::cout << error_message.what() << std::endl;
					}

					catch (RepositoryError& error_message) {
						std::cout << error_message.what() << std::endl;
					}

					catch (FileError& error_message) {
						std::cout << error_message.what() << std::endl;
					}
				}

				else if (strcasecmp(argument, "display")) {
					
					try {
						display_all_events_from_repository();
					}
					
					catch (RepositoryError& error_message) {
						std::cout << error_message.what() << std::endl;
					}

					catch (FileError& error_message) {
						std::cout << error_message.what() << std::endl;
					}

				}

				else if (strcasecmp(argument, "exit"))
					break;

				else
					std::cout << "Unknown command.";

				display_administrator_menu();
			}
		}

		else if (strcasecmp(mode, "user")) {
			if (!list_type_chosen){
				ask_user_for_new_file();
				list_type_chosen = true;
			}

			display_user_menu();

			while (std::getline(std::cin, command)) {
				std::stringstream parser(command);
				std::string argument;
				parser >> argument;

				if (strcasecmp(argument, "mylist")) {
					try {
						display_all_events_from_list();
					}
					
					catch (ListError& error_message) {
						std::cout << error_message.what() << std::endl;
					}

					catch (FileError& error_message) {
						std::cout << error_message.what() << std::endl;
					}
				
				}

				else if (strcasecmp(argument, "delete")) {
					std::string title;
					parser >> argument;
					title = argument;

					while (parser >> argument)
						title += " " + argument;

					try {
						this->controller.remove_event_from_list(title);
						std::cout << "Event has been successfully deleted.\n";
					}

					catch (ValueError& error_message) {
						std::cout << error_message.what() << std::endl;
					}

					catch (ListError& error_message) {
						std::cout << error_message.what() << std::endl;
					}

					catch (FileError& error_message) {
						std::cout << error_message.what() << std::endl;
					}
				}

				else if (strcasecmp(argument, "display")) {
					std::string month;
					parser >> argument;
					month = argument;

					if (month != "display") {
						try {
							Validator::validate_month(month);
						}

						catch (ValueError& error_message) {
							std::cout << error_message.what() << std::endl;
							display_user_menu();
							continue;
						}

						catch (FileError& error_message) {
							std::cout << error_message.what() << std::endl;
						}

						int month_integer = std::stoi(month);

						std::vector<Event> events_for_given_month = this->controller.get_all_unadded_events_for_given_month(month_integer);
						this->controller.sort_events_by_date(events_for_given_month);
						
						int index = 0;

						while (1) {

							if (events_for_given_month.size() == 0) {
								std::cout << "No events left.\n";
								break;
							}

							else {
								Event event = events_for_given_month[index];
								std::cout << event;
								event.open();

								display_list_user_menu();
								std::string event_menu_command;
								std::getline(std::cin, event_menu_command);
								if (strcasecmp(event_menu_command, "add")) {
									try {
										this->controller.add_event_to_list(event);
										events_for_given_month.erase(events_for_given_month.begin() + index);
									}

									catch (FileError& error_message) {
										std::cout << error_message.what() << std::endl;
									}
								}

								else if (strcasecmp(event_menu_command, "next")){
									index++;
									index %= events_for_given_month.size();
								}

								else if (strcasecmp(event_menu_command, "exit"))
									break;

								else
									std::cout << "Unknown command.\n";
							}

						}

					}

					else {
						std::vector<Event> unadded_events = this->controller.get_all_unadded_events();
						this->controller.sort_events_by_date(unadded_events);

						int index = 0;

						while (1) {

							if (unadded_events.size() == 0) {
								std::cout << "No events left.\n";
								break;
							}

							else {
								Event event = unadded_events[index];
								std::cout << event;
								event.open();

								display_list_user_menu();
								std::string event_menu_command;
								std::getline(std::cin, event_menu_command);
								if (strcasecmp(event_menu_command, "add")) {
									try {
										this->controller.add_event_to_list(event);
										unadded_events.erase(unadded_events.begin() + index);
									}

									catch (FileError& error_message) {
										std::cout << error_message.what() << std::endl;
									}
								}

								else if (strcasecmp(event_menu_command, "next")) {
									index++;
									index %= unadded_events.size();
								}

								else if (strcasecmp(event_menu_command, "exit"))
									break;

								else
									std::cout << "Unknown command.\n";
							}

						}

					}
				}

				else if (strcasecmp(argument, "exit"))
					break;

				else
					std::cout << "Unknown command.\n";

				display_user_menu();
			}

		}

		else if (strcasecmp(mode, "exit"))
			break;

		else
			std::cout << "Invalid type provided.\n";
	}
	std::cout << "\nThank you for using the application! See you next time.\n";

}
