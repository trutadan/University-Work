#include "UI.h"

#include <iostream>
#include <sstream>
#include <regex>

UI::UI(Controller& _controller) : controller(_controller)
{
}

void UI::show_all_players() const
{
	std::vector<Player> players = this->controller.get_players();

	if (players.size() == 0) {
		std::cout << "The repository is empty. Add some information!\n";
		return;
	}

	for (Player player : players)
		std::cout << player.player_to_string() << '\n';
}

void UI::show_players_for_given_team(const std::string& searched_team)
{
	std::vector<Player> sorted_players_by_number_of_goals = this->controller.get_sorted_players_by_number_of_goals();

	bool no_players_found = true;
	for (Player player : sorted_players_by_number_of_goals)
		if (player.get_team() == searched_team) {
			std::cout << player.player_to_string() << "\n";
			no_players_found = false;
		}

	if (no_players_found)
		std::cout << "No players found for the given team!\n";
}

void print_menu() {
	std::cout << "\n> add,<name>,<nationality>,<team>,<number_of_players>\n";
	std::cout << "> show all\n";
	std::cout << "> display sorted,<team>\n";
	std::cout << "> exit\n\n";
}

std::vector<std::string> split_command(const std::string& command, char separator) {
	std::vector<std::string> arguments;
	std::string argument;
	std::istringstream argumentStream(command);

	bool single_argument = true;
	while (std::getline(argumentStream, argument, separator)) {
		arguments.push_back(argument);
		single_argument = false;
	}

	if (single_argument == true)
		arguments.push_back(command);

	return arguments;
}

void UI::start_program()
{
	std::vector<std::string> arguments;
	std::string command;

	std::cout << "Welcome to Top Scorer List Manager!\n";

	while (1) {
		print_menu();
		std::cout << "> ";
		getline(std::cin, command);
		arguments = split_command(command, ',');

		if (arguments.size() == 5 && arguments[0] == "add") {
			std::regex pattern("^[0-9]+$");
			if (!std::regex_match(arguments[4], pattern)) {
				std::cout << "The 4th argument needs to be an integer!\n";
				continue;
			}

			Player player{ arguments[1], arguments[2], arguments[3], std::stoi(arguments[4]) };
			bool add_status = this->controller.add_player(player);

			if (add_status == true)
				std::cout << "The player has been successfully added!\n";
			else
				std::cout << "The player has not been added!\n";
		}

		else if (arguments.size() == 1 && arguments[0] == "exit")
			break;

		else if (arguments.size() == 1 && arguments[0] == "show all")
			this->show_all_players();

		else if (arguments.size() == 2 && arguments[0] == "display sorted") {
			this->show_players_for_given_team(arguments[1]);
		}

		else 
			std::cout << "Command unknown.\n";
	}

	std::cout << "Thank you for using our program!\n";

}
