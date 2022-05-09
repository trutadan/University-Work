#pragma once
#include "../Domain/Event.h"
#include "../Functions/Exceptions.h"
#include "../Functions/Functions.h"
#include <vector>

class Repository
{
public:
	Repository();

	virtual bool has_event(const std::string& title);

	virtual int find_event(const std::string& title);

	virtual void add_event(const Event& new_event);

	virtual void remove_event(const std::string& title);

	virtual void update_event(const std::string& title, const std::string& new_description, const Datetime& new_datetime, const int& new_number_of_people, const std::string& new_link);

	virtual std::vector<Event>& get_all_events();

	virtual int get_length();

	std::string get_type() const;

	void set_type(std::string new_type);

	~Repository();

protected:
	std::string type;
	std::vector<Event> events;
};