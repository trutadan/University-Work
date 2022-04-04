#pragma once
#include "DynamicVector.h"
#include "Event.h"

class Repository
{
public:
	Repository(DynamicVector<Event>*);

	bool has_event(const std::string&);

	int find_event(const std::string&);

	void add_event(const Event&);

	void remove_event(const std::string&);

	void update_event(const std::string&, const std::string&, const Datetime&, const int&, const std::string&);

	Event* get_all_events();

	int get_length() const;

	void add_event_without_validation(const Event&);

	~Repository() = default;

private:
	DynamicVector<Event>* events;
};