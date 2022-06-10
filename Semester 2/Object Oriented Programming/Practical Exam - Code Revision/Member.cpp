#include "Member.h"
#include <vector>

Member::Member(const std::string& _name, const int& _umberOfRevisedFiles, const int& _totalNumberOfFilesToRevise)
{
	this->name = _name;
	this->numberOfRevisedFiles = _umberOfRevisedFiles;
	this->totalNumberOfFilesToRevise = _totalNumberOfFilesToRevise;
}

const std::string& Member::getName()
{
	return this->name;
}

const int& Member::getNumberOfRevisedFiles()
{
	return this->numberOfRevisedFiles;
}

void Member::setNumberOfRevisedFiles(const int& number)
{
}

const int& Member::getTotalNumberOfFilesToRevise()
{
	return this->totalNumberOfFilesToRevise;
}

std::istream& operator>>(std::istream& in, Member& member)
{
	std::string line, token;
	std::getline(in, line);
	if (line.empty())
		return in;

	std::stringstream ss(line);
	std::vector<std::string> arguments;

	while (std::getline(ss, token, ';'))
		arguments.push_back(token);

	if (arguments.size() != 3)
		return in;

	member.name = arguments[0];
	member.numberOfRevisedFiles = std::stoi(arguments[1]);
	member.totalNumberOfFilesToRevise = std::stoi(arguments[2]);

	return in;
}
