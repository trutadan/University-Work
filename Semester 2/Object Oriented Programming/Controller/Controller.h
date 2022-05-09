#pragma once
#include "../Repository/Repository.h"
#include "../Repository/TextFileRepository.h"
#include "../Repository/CSVRepository.h"
#include "../Repository/HTMLRepository.h"
#include "../Repository/SQLRepository.h"
#include "../Functions/Functions.h"
#include <iterator>
#include <algorithm>

class Controller
{
public:
	Controller(Repository* _repository, Repository* _list);
	
	std::vector<Event> get_all_events_from_repository();

	int get_repository_length() const;

	void add_event_to_repository(const std::string& title, const std::string& description, const Datetime& datetime, const int& number_of_people, const std::string& link);

	void remove_event_from_repository(const std::string& title);

	void update_event_from_repository(const std::string& title, const std::string& new_description, const Datetime& new_datetime, const int& new_number_of_people, const std::string& new_link);

	std::vector<Event> get_all_events_from_list();

	int get_list_length() const;

	void add_event_to_list(const Event& new_event);

	void remove_event_from_list(const std::string& title);

	bool is_event_from_repository_in_list(const std::string& title);

	std::vector<Event> get_all_unadded_events_for_given_month(const int& month);

	std::vector<Event> get_all_unadded_events();

	void sort_events_by_date(std::vector<Event>&);

	void change_admin_repository_type(const std::string& repository_type);

	void change_user_repository_type(const std::string& repository_type);

	std::string get_repository_type() const;

	std::string get_list_type() const;

	void open_repository_file();

	void open_list_file();

	~Controller() = default;

private:
	Repository* repository;
	Repository* list;
};

