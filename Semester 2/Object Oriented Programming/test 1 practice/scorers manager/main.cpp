#include <iostream>
#include "UI.h"
#include <cassert>


void add_entries_at_startup(Controller& controller) {
	controller.add_player(Player{ "abc", "EN", "FC Voluntari", 78 });
	controller.add_player(Player{ "def", "DE", "FC Cojasca", 15 });
	controller.add_player(Player{ "ghi", "RU", "FC Farul Constanta", 43 });
	controller.add_player(Player{ "jkl", "FR", "FC U Craiova", 13 });
	controller.add_player(Player{ "mno", "DK", "FC Dinamo", 34 });
}

void test_controller_add_player() {
	Player player_to_be_added{ "Dan", "RO", "FC Dinamo", 53 };
	Repository repository;
	Controller controller{ repository };
	bool add_status;

	add_status = controller.add_player(player_to_be_added);

	assert(add_status == true);

	std::vector<Player> players = controller.get_players();

	assert(players.size() == 1);

	Player player = players[0];

	assert(player.get_name() == "Dan");
	assert(player.get_team() == "FC Dinamo");
	assert(player.get_number_of_goals() == 53);

	add_status = controller.add_player(player_to_be_added);
	
	assert(add_status == false);
}

void test_controller_get_sorted_players_by_number_of_goals() {
	Player player_to_be_added{ "Dan", "RO", "FC Dinamo", 53 };
	Player another_player_to_be_added{ "Bogdan", "RO", "FCSB", 41 };
	Repository repository;
	Controller controller{ repository };

	controller.add_player(player_to_be_added);
	controller.add_player(another_player_to_be_added);

	std::vector<Player> players_sorted = controller.get_sorted_players_by_number_of_goals();

	assert(players_sorted[0].get_number_of_goals() == 41);
	assert(players_sorted[1].get_number_of_goals() == 53);
}

int main()
{
	{
		test_controller_add_player();
		test_controller_get_sorted_players_by_number_of_goals();
	}

	{
		Repository repository;
		Controller controller{ repository };
		add_entries_at_startup(controller);
		UI ui{ controller };

		ui.start_program();
	}
}
