#pragma once
#include <string>
#define CURRENT_YEAR 2022

class Building
{
public:
	Building();

	Building(const std::string&, const int&);

	virtual bool mustBeRestored() = 0;

	virtual bool canBeDemolished() = 0;

	virtual std::string toString() = 0;

	int get_constructionYear() const;

	~Building();

protected:
	std::string address;
	int constructionYear;
};

