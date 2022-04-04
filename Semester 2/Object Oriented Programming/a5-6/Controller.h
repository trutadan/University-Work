#pragma once
#include "Repository.h"
#include "Functions.h"

class Controller
{
public:
	Controller(Repository*, Repository*, Repository*);
	
	Event* get_all_events_from_repository();

	int get_repository_length() const;

	void add_event_to_repository(const std::string&, const std::string&, const Datetime&, const int&, const std::string&);

	void remove_event_from_repository(const std::string&);

	void update_event_from_repository(const std::string&, const std::string&, const Datetime&, const int&, const std::string&);

	Event* get_all_events_from_list();

	int get_list_length() const;

	void add_event_to_list(const Event&);

	void remove_event_from_list(const std::string&);

	bool is_event_from_repository_in_list(const std::string&);

	DynamicVector<Event>* get_all_unadded_events_for_given_month(const int);

	DynamicVector<Event>* get_all_unadded_events();

	void sort_events_by_date(Event*, const int&);

	Event* get_removed_events_from_repository();

	int get_removal_history_length() const;

	~Controller() = default;

private:
	Repository* repository;
	Repository* list;
	Repository* removal_history;
};

