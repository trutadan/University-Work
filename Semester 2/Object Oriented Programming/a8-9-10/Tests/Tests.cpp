#include "Tests.h"
#include "../Domain/Datetime.h"
#include "../Domain/Event.h"
#include "../Functions/Functions.h"
#include "../Functions/DynamicVector.h"
#include "../Repository/Repository.h"
#include "../Functions/Exceptions.h"
#include "../Controller/Controller.h"
#include <cassert>

void test_getters__random_datetime_instance__successfully_working()
{
	Datetime datetime{ 2022, 4, 17, 13, 26 };

	assert(datetime.get_year() == 2022);
	assert(datetime.get_month() == 4);
	assert(datetime.get_day() == 17);

	assert(datetime.get_hour() == 13);
	assert(datetime.get_minutes() == 26);

	assert(datetime.date_to_string() == "17/4/2022");
	assert(datetime.time_to_string() == "13:26");
}

void test_setters__random_datetime_instance__successfully_working()
{
	Datetime datetime{ 2022, 4, 17, 13, 26 };

	datetime.set_year(2022);
	datetime.set_month(7);
	datetime.set_day(30);
	
	assert(datetime.get_year() == 2022);
	assert(datetime.get_month() == 7);
	assert(datetime.get_day() == 30);

	datetime.set_hour(23);
	datetime.set_minutes(52);

	assert(datetime.get_hour() == 23);
	assert(datetime.get_minutes() == 52);
}

void test_equal_operator__same_datetime__equality_checked()
{
	Datetime datetime{ 2022, 4, 17, 13, 26 };
	Datetime same_datetime{ 2022, 4, 17, 13, 26 };

	bool equality_checker = datetime == same_datetime;

	assert(equality_checker == true);
}

void test_to_string__random_datetime__correct_string()
{
	Datetime datetime{ 2022, 4, 17, 13, 6 };

	assert(datetime.date_to_string() == "2022/4/17");
	assert(datetime.time_to_string() == "13:06");
}

void test_datetime()
{
	test_getters__random_datetime_instance__successfully_working();
	test_setters__random_datetime_instance__successfully_working();
	test_equal_operator__same_datetime__equality_checked();
	test_to_string__random_datetime__correct_string();
}

void test_getters__random_event_instance__successfully_working()
{
	Datetime datetime{ 2022, 4, 17, 13, 26 };
	Event event{ "Pierdut printre stele", "Joc de tip Treasure Hunt combinat cu multe elemente de Escape Room", datetime, 143, "https://www.clujlife.com/eveniment/pierdut-printre-stele/" };

	assert(event.get_title() == "Pierdut printre stele");
	assert(event.get_description() == "Joc de tip Treasure Hunt combinat cu multe elemente de Escape Room");
	assert(event.get_datetime() == datetime);
	assert(event.get_number_of_people() == 143);
	assert(event.get_link() == "https://www.clujlife.com/eveniment/pierdut-printre-stele/");
}

void test_setters__random_event_instance__successfully_working()
{
	Datetime datetime{ 2022, 4, 17, 13, 26 };
	Event event{ "Pierdut printre stele", "Joc de tip Treasure Hunt combinat cu multe elemente de Escape Room", datetime, 143, "https://www.clujlife.com/eveniment/pierdut-printre-stele/" };

	Datetime other_datetime{ 2022, 7, 30, 23, 52 };

	event.set_description("Evenimentul va avea loc in aer liber");
	event.set_datetime(other_datetime);
	event.set_number_of_people(457);
	event.set_link("https://www.clujlife.com/eveniment/");

	assert(event.get_title() == "Pierdut printre stele");
	assert(event.get_description() == "Evenimentul va avea loc in aer liber");
	assert(event.get_datetime() == other_datetime);
	assert(event.get_number_of_people() == 457);
	assert(event.get_link() == "https://www.clujlife.com/eveniment/");
}

void test_equal_operator__same_event__equality_checked()
{
	Datetime datetime{ 2022, 4, 17, 13, 26 };
	Event event{ "Pierdut printre stele", "Joc de tip Treasure Hunt combinat cu multe elemente de Escape Room", datetime, 143, "https://www.clujlife.com/eveniment/pierdut-printre-stele/" };

	Datetime other_datetime{ 2022, 5, 21, 12, 30 };
	Event other_event{ "Pierdut printre stele", "cu Simona Halep, Gheorghe Hagi, Horia Tecau si Adrian Mutu", other_datetime, 3421, "https://www.clujlife.com/eveniment/sports-festival-2022/" };

	bool equality_checker = event == other_event;

	assert(equality_checker == true);
}

void test_event()
{
	test_getters__random_event_instance__successfully_working();
	test_setters__random_event_instance__successfully_working();
	test_equal_operator__same_event__equality_checked();
}

void test_strip__random_strings_with_spaces__spaces_successfully_removed()
{
	std::string first_example = "         hell o  ";
	strip(first_example);
	assert(first_example == "hell o");

	std::string second_example = "\t     he  \t l \n";
	strip(second_example);
	assert(second_example == "he  \t l");

	std::string third_example = "\t       \t  \n";
	strip(third_example);
	assert(third_example == "");
}

void test_split__random_strings_and_delimiters__string_successfully_split_into_parts()
{
	std::string first_example = "agh/hell/oo";
	std::vector<std::string> first_example_split = split(first_example, '/');
	assert(first_example_split.size() == 3);

	std::string second_example = "hello, what      , not,,,";
	std::vector<std::string> second_example_split = split(second_example, ',');
	assert(second_example_split.size() == 5);
	assert(second_example_split[0] == "hello");
	assert(second_example_split[1] == " what      ");
	assert(second_example_split[2] == " not");
	assert(second_example_split[3] == "");
	assert(second_example_split[4] == "");
}

void test_strcasecmp__random_strings__correct_comparison()
{
	assert(strcasecmp("hello", "HelLO") == true);
	
	assert(strcasecmp("q", "werty") == false);
	
	assert(strcasecmp("A", "a ") == false);

	assert(strcasecmp("NO", "no") == true);
	
	assert(strcasecmp("123!", "123!") == true);
}

void test_check_sooner_event__various_events_of_different_date_or_time__correct_comparison()
{
	Datetime datetime{ 2022, 4, 17, 13, 26 };
	Event event{ "", "", datetime, 0, "" };

	Datetime other_datetime{ 2022, 4, 17, 1, 56 };
	Event same_day_sooner_event{ "", "", other_datetime, 0, "" };

	assert(check_sooner_event(same_day_sooner_event, event));

	Datetime another_datetime{ 2022, 2, 17, 11, 31 };
	Event most_soon_event{ "", "", another_datetime, 0, "" };

	assert(check_sooner_event(most_soon_event, same_day_sooner_event));

	Datetime same_datetime{ 2022, 2, 17, 11, 31 };
	Event same_event{ "", "", another_datetime, 0, "" };

	assert(check_sooner_event(most_soon_event, same_event));
}

void test_functions()
{
	test_strip__random_strings_with_spaces__spaces_successfully_removed();
	test_split__random_strings_and_delimiters__string_successfully_split_into_parts();
	test_strcasecmp__random_strings__correct_comparison();
	test_check_sooner_event__various_events_of_different_date_or_time__correct_comparison();
}

void test_dynamicVector() {
	typedef void* TypeOfElement;

	DynamicVector<TypeOfElement>* dynamic_vector = new DynamicVector<TypeOfElement>;

	assert(dynamic_vector->get_length() == 0);

	TypeOfElement element1 = nullptr;
	dynamic_vector->add(element1);
	assert(dynamic_vector->get_length() == 1);

	TypeOfElement element2 = nullptr;
	dynamic_vector->add(element2);
	assert(dynamic_vector->get_length() == 2);

	TypeOfElement element3 = nullptr;
	dynamic_vector->update(1, element3);
	assert(dynamic_vector->get_elements()[1] == element3);

	TypeOfElement element4 = nullptr;
	dynamic_vector->add(element4);
	dynamic_vector->remove(1);
	assert(dynamic_vector->get_length() == 2);
	assert(dynamic_vector->get_elements()[1] == element4);

	delete dynamic_vector;
}

void test_repository_add__new_event__event_successfully_added()
{
	Repository repo;

	Datetime datetime{ 2022, 4, 17, 13, 26 };
	Event event{ "Pierdut printre stele", "Joc de tip Treasure Hunt combinat cu multe elemente de Escape Room", datetime, 143, "https://www.clujlife.com/eveniment/pierdut-printre-stele/" };

	assert(repo.get_length() == 0);

	repo.add_event(event);

	assert(repo.get_length() == 1);
}

void test_repository_add__existent_event__throws_exception()
{
	Repository repo;

	Datetime datetime{ 2022, 4, 17, 13, 26 };
	Event event{ "Pierdut printre stele", "Joc de tip Treasure Hunt combinat cu multe elemente de Escape Room", datetime, 143, "https://www.clujlife.com/eveniment/pierdut-printre-stele/" };

	assert(repo.get_length() == 0);

	repo.add_event(event);

	assert(repo.get_length() == 1);

	Event another_event{ "pierdut printre Stele", "Evenimentul va avea loc in aer liber", datetime, 513, "https://www.clujlife.com/eveniment" };

	bool exception_thrown = false;

	try
	{
		repo.add_event(another_event);
	}

	catch (RepositoryError&)
	{
		exception_thrown = true;
	}

	assert(exception_thrown);

	assert(repo.get_length() == 1);
}

void test_repository_remove__existent_title__event_successfully_removed()
{
	Repository repo;

	Datetime datetime{ 2022, 4, 17, 13, 26 };
	Event event{ "Pierdut printre stele", "Joc de tip Treasure Hunt combinat cu multe elemente de Escape Room", datetime, 143, "https://www.clujlife.com/eveniment/pierdut-printre-stele/" };

	repo.add_event(event);

	assert(repo.get_length() == 1);

	repo.remove_event("pierdut printre stele");

	assert(repo.get_length() == 0);
}

void test_repository_remove__inexistent_title__throws_exception()
{
	Repository repo;

	Datetime datetime{ 2022, 4, 17, 13, 26 };
	Event event{ "Pierdut printre stele", "Joc de tip Treasure Hunt combinat cu multe elemente de Escape Room", datetime, 143, "https://www.clujlife.com/eveniment/pierdut-printre-stele/" };

	repo.add_event(event);

	assert(repo.get_length() == 1);

	bool exception_thrown = false;

	try
	{
		repo.remove_event("random title");
	}

	catch (RepositoryError&)
	{
		exception_thrown = true;
	}

	assert(exception_thrown);

	assert(repo.get_length() == 1);
}

void test_repository_update__existent_title__event_successfully_updated()
{
	Repository repo;

	Datetime datetime{ 2022, 4, 17, 13, 26 };
	Event event{ "Pierdut printre stele", "Joc de tip Treasure Hunt combinat cu multe elemente de Escape Room", datetime, 143, "https://www.clujlife.com/eveniment/pierdut-printre-stele/" };

	repo.add_event(event);

	assert(repo.get_length() == 1);

	repo.update_event("Pierdut printre stele", "new description", datetime, 235, "new link");

	Event updated_event = repo.get_all_events()[0];

	assert(updated_event.get_title() == "Pierdut printre stele");
	assert(updated_event.get_description() == "new description");
	assert(updated_event.get_number_of_people() == 235);
	assert(updated_event.get_link() == "new link");
}

void test_repository_update__inexistent_title__throws_exception()
{
	Repository repo;

	Datetime datetime{ 2022, 4, 17, 13, 26 };
	Event event{ "Pierdut printre stele", "Joc de tip Treasure Hunt combinat cu multe elemente de Escape Room", datetime, 143, "https://www.clujlife.com/eveniment/pierdut-printre-stele/" };

	repo.add_event(event);

	assert(repo.get_length() == 1);

	bool exception_thrown = false;

	try
	{
		repo.update_event("random title", "new description", datetime, 321, "new link");
	}

	catch (RepositoryError&)
	{
		exception_thrown = true;
	}

	assert(exception_thrown);

	assert(repo.get_length() == 1);

	Event event_from_repo = repo.get_all_events()[0];

	assert(event_from_repo.get_title() == "Pierdut printre stele");
	assert(event_from_repo.get_description() == "Joc de tip Treasure Hunt combinat cu multe elemente de Escape Room");
	assert(event_from_repo.get_number_of_people() == 143);
	assert(event_from_repo.get_link() == "https://www.clujlife.com/eveniment/pierdut-printre-stele/");
}

void test_repository_get_all_events__check_events__correct_events()
{
	Repository repo;

	Datetime datetime{ 2022, 4, 17, 13, 26 };
	Event event{ "Pierdut printre stele", "Joc de tip Treasure Hunt combinat cu multe elemente de Escape Room", datetime, 143, "https://www.clujlife.com/eveniment/pierdut-printre-stele/" };

	Datetime other_datetime{ 2022, 5, 21, 12, 30 };
	Event other_event{ "Sports Festival 2022", "cu Simona Halep, Gheorghe Hagi, Horia Tecau si Adrian Mutu", other_datetime, 3421, "https://www.clujlife.com/eveniment/sports-festival-2022/" };

	repo.add_event(event);
	repo.add_event(other_event);

	std::vector<Event> events = repo.get_all_events();
	
	assert(events[0] == event);
	assert(events[1] == other_event);

	assert(events[0].get_title() == "Pierdut printre stele");
	assert(events[1].get_title() == "Sports Festival 2022");
}

void test_repository()
{
	test_repository_add__new_event__event_successfully_added();
	test_repository_add__existent_event__throws_exception();
	test_repository_remove__existent_title__event_successfully_removed();
	test_repository_remove__inexistent_title__throws_exception();
	test_repository_update__existent_title__event_successfully_updated();
	test_repository_update__inexistent_title__throws_exception();
	test_repository_get_all_events__check_events__correct_events();
}

void test_add_event_to_repository__new_event__event_successfully_added()
{
	Repository* list = new Repository;
	Repository* repository = new Repository;

	Controller controller{ repository, list };

	assert(controller.get_repository_length() == 0);

	std::string title = "Pierdut printre stele";
	std::string description = "Joc de tip Treasure Hunt combinat cu multe elemente de Escape Room";
	Datetime datetime{ 2022, 4, 17, 13, 26 };
	int number_of_people = 143;
	std::string link = "https://www.clujlife.com/eveniment/pierdut-printre-stele/";

	controller.add_event_to_repository(title, description, datetime, number_of_people, link);

	assert(controller.get_repository_length() == 1);
}

void test_remove_event_from_repository__existent_event__event_successfully_removed()
{
	Repository* list = new Repository;
	Repository* repository = new Repository;

	Controller controller{ repository, list };

	assert(controller.get_repository_length() == 0);

	std::string title = "Pierdut printre stele";
	std::string description = "Joc de tip Treasure Hunt combinat cu multe elemente de Escape Room";
	Datetime datetime{ 2022, 4, 17, 13, 26 };
	int number_of_people = 143;
	std::string link = "https://www.clujlife.com/eveniment/pierdut-printre-stele/";

	controller.add_event_to_repository(title, description, datetime, number_of_people, link);

	assert(controller.get_repository_length() == 1);

	controller.remove_event_from_repository("pierdut printre stelE");

	assert(controller.get_repository_length() == 0);
}

void test_update_event_from_repository__existent_event__event_successfully_updated()
{
	Repository* list = new Repository;
	Repository* repository = new Repository;

	Controller controller{ repository, list };

	assert(controller.get_repository_length() == 0);

	std::string title = "Pierdut printre stele";
	std::string description = "Joc de tip Treasure Hunt combinat cu multe elemente de Escape Room";
	Datetime datetime{ 2022, 4, 17, 13, 26 };
	int number_of_people = 143;
	std::string link = "https://www.clujlife.com/eveniment/pierdut-printre-stele/";

	controller.add_event_to_repository(title, description, datetime, number_of_people, link);

	assert(controller.get_repository_length() == 1);

	controller.update_event_from_repository("pierdut printre stelE", "new description", datetime, 731, "new link");

	Event updated_event = controller.get_all_events_from_repository()[0];

	assert(updated_event.get_title() == "pierdut printre stelE");
	assert(updated_event.get_description() == "new description");
	assert(updated_event.get_number_of_people() == 731);
	assert(updated_event.get_link() == "new link");
}

void test_add_event_to_list__new_event__event_successfully_added_in_list_and_updated_in_repository()
{
	Repository* list = new Repository;
	Repository* repository = new Repository;

	Controller controller{ repository, list };

	std::string title = "Pierdut printre stele";
	std::string description = "Joc de tip Treasure Hunt combinat cu multe elemente de Escape Room";
	Datetime datetime{ 2022, 4, 17, 13, 26 };
	int number_of_people = 143;
	std::string link = "https://www.clujlife.com/eveniment/pierdut-printre-stele/";

	controller.add_event_to_repository(title, description, datetime, number_of_people, link);

	Event added_event = controller.get_all_events_from_repository()[0];

	assert(added_event.get_number_of_people() == 143);

	controller.add_event_to_list(added_event);

	Event updated_event = controller.get_all_events_from_repository()[0];

	assert(updated_event.get_number_of_people() == 144);

	controller.remove_event_from_list(added_event.get_title());

	updated_event = controller.get_all_events_from_repository()[0];

	assert(updated_event.get_number_of_people() == 143);
}

void test_get_all_unadded_events_for_given_month__different_cases_when_events_are_both_in_list_and_repository_or_not__successfully_working()
{
	Datetime first_datetime{ 0, 1, 0, 0, 0 };
	Datetime second_datetime{ 6, 1, 2, 7, 12 };
	Datetime third_datetime{ 1, 10, 2, 5, 35 };

	Event first_event{ "first event", "1", first_datetime, 10, "link" };
	Event second_event{ "second event", "2", second_datetime, 123, "link" };
	Event third_event{ "third event", "3", third_datetime, 74, "link" };

	Repository* repository = new Repository;
	repository->add_event(first_event);
	repository->add_event(second_event);
	repository->add_event(third_event);

	Repository* list = new Repository;

	Controller controller{ repository, list };

	assert(controller.get_repository_length() == 3);

	std::vector<Event> filtered_event_for_month_one = controller.get_all_unadded_events_for_given_month(1);

	assert(filtered_event_for_month_one.size() == 2);

	controller.add_event_to_list(second_event);

	filtered_event_for_month_one = controller.get_all_unadded_events_for_given_month(1);

	assert(filtered_event_for_month_one.size() == 1);
}

void test_get_all_unadded_events__different_cases_when_events_are_both_in_list_and_repository_or_not__successfully_working()
{
	Datetime first_datetime{ 0, 1, 0, 0, 0 };
	Datetime second_datetime{ 6, 1, 2, 7, 12 };
	Datetime third_datetime{ 1, 10, 2, 5, 35 };

	Event first_event{ "first event", "1", first_datetime, 10, "link" };
	Event second_event{ "second event", "2", second_datetime, 123, "link" };
	Event third_event{ "third event", "3", third_datetime, 74, "link" };

	Repository* repository = new Repository;
	repository->add_event(first_event);
	repository->add_event(second_event);
	repository->add_event(third_event);

	Repository* list = new Repository;

	Controller controller{ repository, list };

	assert(controller.get_repository_length() == 3);

	std::vector<Event> filtered_event_for_month_one = controller.get_all_unadded_events();

	assert(filtered_event_for_month_one.size() == 3);

	controller.add_event_to_list(first_event);

	filtered_event_for_month_one = controller.get_all_unadded_events();

	assert(filtered_event_for_month_one.size() == 2);

	controller.add_event_to_list(second_event);

	filtered_event_for_month_one = controller.get_all_unadded_events();

	assert(filtered_event_for_month_one.size() == 1);

	controller.remove_event_from_list(second_event.get_title());

	filtered_event_for_month_one = controller.get_all_unadded_events();

	assert(filtered_event_for_month_one.size() == 2);

	controller.add_event_to_list(second_event);

	filtered_event_for_month_one = controller.get_all_unadded_events();

	assert(filtered_event_for_month_one.size() == 1);

	controller.add_event_to_list(third_event);

	filtered_event_for_month_one = controller.get_all_unadded_events();

	assert(filtered_event_for_month_one.size() == 0);
}

void test_sort_events_by_date__different_dates_from_same_year__successfully_sorted()
{
	Datetime first_datetime{ 1, 1, 0, 0, 0 };
	Datetime second_datetime{ 1, 11, 2, 7, 12 };
	Datetime third_datetime{ 1, 10, 2, 5, 35 };

	Event first_event{ "first event", "1", first_datetime, 10, "link" };
	Event second_event{ "second event", "2", second_datetime, 123, "link" };
	Event third_event{ "third event", "3", third_datetime, 74, "link" };

	Repository* repository = new Repository;
	repository->add_event(first_event);
	repository->add_event(second_event);
	repository->add_event(third_event);

	Repository* list = new Repository;

	Controller controller{ repository, list };

	std::vector<Event> events = controller.get_all_events_from_repository();

	controller.sort_events_by_date(events);

	assert(events[0].get_title() == "first event");
	assert(events[1].get_title() == "third event");
	assert(events[2].get_title() == "second event");
}

void test_controller()
{
	test_add_event_to_repository__new_event__event_successfully_added();
	test_remove_event_from_repository__existent_event__event_successfully_removed();
	test_update_event_from_repository__existent_event__event_successfully_updated();
	test_add_event_to_list__new_event__event_successfully_added_in_list_and_updated_in_repository();
	test_get_all_unadded_events_for_given_month__different_cases_when_events_are_both_in_list_and_repository_or_not__successfully_working();
	test_get_all_unadded_events__different_cases_when_events_are_both_in_list_and_repository_or_not__successfully_working();
	test_sort_events_by_date__different_dates_from_same_year__successfully_sorted();
}

void test_all_functionalities()
{
	test_datetime();
	test_event();
	test_functions();
	test_dynamicVector();
	test_repository();
	test_controller();
}
