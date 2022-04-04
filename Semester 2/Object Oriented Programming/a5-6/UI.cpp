#include <iostream>
#include "UI.h"
#include "Exceptions.h"
#include "Validator.h"

UI::UI(Controller* _controller) : controller(_controller)
{
}

void display_administrator_menu()
{
	std::cout << "\n> add <title>,<description>,<date>,<time>,<number of people>,<link>\n";
	std::cout << "> delete <title>\n";
	std::cout << "> update <title>,<new description>,<new date>,<new time>,<new number of people>,<new link>\n";
	std::cout << "> display\n";
	std::cout << "> history\n";
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

void add_entries_at_startup(Controller* controller)
{
	controller->add_event_to_repository("Singles Party Charlie", "Vrei sa-ti faci noi prieteni, sa te bucuri de libertate si un orar fara restrictii, sa canti si sa dansezi?", Datetime{ 26,3,2022,7,30 }, 150, "https://www.clujlife.com/eveniment/singles-party-charlie/");
	controller->add_event_to_repository("CLOSER v.1", "With the departure process coming to an end, the rivers flow free through the melted barriers. It is time to return closer to the core", Datetime{ 1,3,2022,8,0 }, 25, "https://www.clujlife.com/eveniment/closer-v-1/");
	controller->add_event_to_repository("Retro gaming LAN Party", " O zi in care poti sa joci câteva jocuri video retro (pe console si PC) la noi în spatiu.", Datetime{ 3,4,2022,14,15 }, 206, "https://www.clujlife.com/eveniment/retro-gaming-lan-party-3/2022-04-03/");
	controller->add_event_to_repository("Fancy Garage Sale – 10th Edition", "Va invitam la o dupa - masa de targuiala vesela, un fel de OSER mai fancy cu articole atat vechi, cat si noi.", Datetime{ 3,4,2022,16,30 }, 27, "https://www.clujlife.com/eveniment/fancy-garage-sale-10th-edition-urania-palace/");
	controller->add_event_to_repository("Fools Comedy Days", "Se numeste „Fools Comedy Days – Cluj” si dureaza 3 zile.", Datetime{ 15,5,2022,19,15 }, 206, "https://www.clujlife.com/eveniment/fools-comedy-days-iulius-parc-cluj-napoca/");
	controller->add_event_to_repository("The INNER – Mapping inside", "Mappingx Inside este primul eveniment de invatare ai practica din Romania, dedicat starii de bine si sanatatii corp-minte-suflet.", Datetime{ 3,6,2022,15,30 }, 54, "https://www.clujlife.com/eveniment/the-inner-mapping-inside/");
	controller->add_event_to_repository("Jazz in the Park 2022", "In 1-4 septembrie 2022, ne revedem in Parcul Etnografic din Cluj-Napoca. Va fi jazz, asa ca ramai pe-aproape. Mai multe detalii in curand.", Datetime{ 1,9,2022,18,0 }, 452, "https://www.clujlife.com/eveniment/jazz-in-the-park-2022/");
	controller->add_event_to_repository("UNTOLD FESTIVAL 2022", "Together we will write a new chapter of the UNTOLD story! See you on the 4th of August 2022", Datetime{ 7,8,2022,10,0 }, 12254, "https://www.clujlife.com/eveniment/untold-festival-2022/");
	controller->add_event_to_repository("Electric Castle 2022", "Electric Castle is a one-of-a-kind music festival happening between July 13-17 2022, at Banffy Castle in Transylvania.", Datetime{ 13,7,2022,11,30 }, 5154, "https://www.clujlife.com/eveniment/electric-castle-2022/");
	controller->add_event_to_repository("Jimmy Carr – Live in Cluj", "Jimmy Carr pune Cluj-Napoca pe harta celui mai recent turneu de stand up comedy pe care l-a lansat – TERRIBLY FUNNY.", Datetime{ 1,10,2022,19,0 }, 74, "https://www.clujlife.com/eveniment/jimmy-carr-live-in-cluj/");
}

void UI::display_all_events_from_repository()
{
	int number_of_events = this->controller->get_repository_length();

	if (number_of_events == 0) {
		throw RepositoryError("There are no events in the database. Add some.\n");
	}

	Event* list_of_events = this->controller->get_all_events_from_repository();
	int events_list_length = this->controller->get_repository_length();
	this->controller->sort_events_by_date(list_of_events, events_list_length);

	std::cout << "title,description,date,hour,number of people,link\n";
	std::cout << "-------------------------------------------------\n";

	for (int index = 0; index < number_of_events; index++) {
		Event event = list_of_events[index];
		std::cout << index + 1 << ". " << event.get_title() << ", " << event.get_description() << ", " << event.get_datetime().datetime_to_string() << ", " << event.get_number_of_people() << ", " << event.get_link() << std::endl;
	}
}

void UI::display_all_events_from_list()
{
	int number_of_events = this->controller->get_list_length();

	if (number_of_events == 0) {
		throw ListError("There are no events in the list. Add some.\n");
	}

	Event* list_of_events = this->controller->get_all_events_from_list();
	int events_list_length = this->controller->get_list_length();
	this->controller->sort_events_by_date(list_of_events, events_list_length);

	std::cout << "title,description,date,hour,number of people,link\n";
	std::cout << "-------------------------------------------------\n";

	for (int index = 0; index < number_of_events; index++) {
		Event event = list_of_events[index];
		std::cout << index + 1 << ". " << event.get_title() << ", " << event.get_description() << ", " << event.get_datetime().datetime_to_string() << ", " << event.get_number_of_people() << ", " << event.get_link() << std::endl;
	}
}

void UI::display_all_events_from_removal_history()
{
	int number_of_events = this->controller->get_removal_history_length();

	if (number_of_events == 0) {
		throw RepositoryError("There are no events in the removal history. Add some.\n");
	}

	Event* list_of_events = this->controller->get_removed_events_from_repository();
	int events_list_length = this->controller->get_list_length();
	this->controller->sort_events_by_date(list_of_events, events_list_length);

	std::cout << "title,description,date,hour,number of people,link\n";
	std::cout << "-------------------------------------------------\n";

	for (int index = 0; index < number_of_events; index++) {
		Event event = list_of_events[index];
		std::cout << index + 1 << ". " << event.get_title() << ", " << event.get_description() << ", " << event.get_datetime().datetime_to_string() << ", " << event.get_number_of_people() << ", " << event.get_link() << std::endl;
	}
}

void UI::start_program()
{
	std::cout << "Welcome to 'Life after School' program!\n";
	std::string mode;

	add_entries_at_startup(this->controller);

	while (1) {
		std::cout << "\n'admin', 'user', 'exit'? \n";

		std::cout << "> ";
		std::getline(std::cin, mode);

		std::string command;

		if (strcasecmp(mode, "admin")) {
			display_administrator_menu();

			while (std::getline(std::cin, command)) {
				std::stringstream parser(command);
				std::string argument;
				parser >> argument;

				if (strcasecmp(argument, "add")) {
					Event event;

					try {
						parser >> event;
						this->controller->add_event_to_repository(event.get_title(), event.get_description(), event.get_datetime(), event.get_number_of_people(), event.get_link());
						std::cout << "Event has been successfully added.\n";
					}

					catch (ValueError& error_message) {
						std::cout << error_message.what() << std::endl;
					}

					catch (RepositoryError& error_message) {
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
						this->controller->remove_event_from_repository(title);
						std::cout << "Event has been successfully deleted.\n";
					}

					catch (ValueError& error_message) {
						std::cout << error_message.what() << std::endl;
					}

					catch (RepositoryError& error_message) {
						std::cout << error_message.what() << std::endl;
					}

				}

				else if (strcasecmp(argument, "update")) {
					Event event;

					try {
						parser >> event;
						this->controller->update_event_from_repository(event.get_title(), event.get_description(), event.get_datetime(), event.get_number_of_people(), event.get_link());
						std::cout << "Event has been successfully updated.\n";
					}

					catch (ValueError& error_message) {
						std::cout << error_message.what() << std::endl;
					}

					catch (RepositoryError& error_message) {
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

				}

				else if (strcasecmp(argument, "history")) {

					try {
						display_all_events_from_removal_history();
					}

					catch (RepositoryError& error_message) {
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
				
				}

				else if (strcasecmp(argument, "delete")) {
					std::string title;
					parser >> argument;
					title = argument;

					while (parser >> argument)
						title += " " + argument;

					try {
						this->controller->remove_event_from_list(title);
						std::cout << "Event has been successfully deleted.\n";
					}

					catch (ValueError& error_message) {
						std::cout << error_message.what() << std::endl;
					}

					catch (ListError& error_message) {
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

						int month_integer = std::stoi(month);

						DynamicVector<Event>* events_for_given_month = this->controller->get_all_unadded_events_for_given_month(month_integer);
						int events_list_length = events_for_given_month->get_length();
						this->controller->sort_events_by_date(events_for_given_month->get_elements(), events_list_length);
						
						int index = 0;

						while (1) {

							if (events_for_given_month->get_length() == 0) {
								std::cout << "No events left.\n";
								break;
							}

							else {
								Event event = events_for_given_month->get_elements()[index];
								std::cout << event.get_title() << ", " << event.get_description() << ", " << event.get_datetime().datetime_to_string() << ", " << event.get_number_of_people() << ", " << event.get_link();
								event.open();

								display_list_user_menu();
								std::string event_menu_command;
								std::getline(std::cin, event_menu_command);
								if (strcasecmp(event_menu_command, "add")) {
									this->controller->add_event_to_list(event);
									events_for_given_month->remove(index);
								}

								else if (strcasecmp(event_menu_command, "next")){
									index++;
									index %= events_for_given_month->get_length();
								}

								else if (strcasecmp(event_menu_command, "exit"))
									break;

								else
									std::cout << "Unknown command.\n";
							}

						}

						delete events_for_given_month;

					}

					else {
						DynamicVector<Event>* unadded_events = this->controller->get_all_unadded_events();
						int events_list_length = unadded_events->get_length();
						this->controller->sort_events_by_date(unadded_events->get_elements(), events_list_length);

						int index = 0;

						while (1) {

							if (unadded_events->get_length() == 0) {
								std::cout << "No events left.\n";
								break;
							}

							else {
								Event event = unadded_events->get_elements()[index];
								std::cout << event.get_title() << ", " << event.get_description() << ", " << event.get_datetime().datetime_to_string() << ", " << event.get_number_of_people() << ", " << event.get_link();
								event.open();

								display_list_user_menu();
								std::string event_menu_command;
								std::getline(std::cin, event_menu_command);
								if (strcasecmp(event_menu_command, "add")) {
									this->controller->add_event_to_list(event);
									unadded_events->remove(index);
								}

								else if (strcasecmp(event_menu_command, "next")) {
									index++;
									index %= unadded_events->get_length();
								}

								else if (strcasecmp(event_menu_command, "exit"))
									break;

								else
									std::cout << "Unknown command.\n";
							}

						}

						delete unadded_events;

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
