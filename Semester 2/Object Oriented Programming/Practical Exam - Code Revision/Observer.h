#pragma once
#include <vector>

class Observer
{
public:
	Observer() {}

	virtual void update() = 0;

	~Observer() {}
};

class Subject
{
private:
	std::vector<Observer*> repo;

public:
	void addObserver(Observer* obs);

	void removeObserver(Observer* obs);

	void notify();
};
