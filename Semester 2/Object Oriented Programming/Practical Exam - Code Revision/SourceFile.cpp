#include "SourceFile.h"

SourceFile::SourceFile(const std::string& _name, const std::string& _status, const std::string& _creator, const std::string& _reviewer)
{
	this->name = _name;
	this->status = _status;
	this->creator = _creator;
	this->reviewer = _reviewer;
}

const std::string& SourceFile::getName()
{
	return this->name;
}

const std::string& SourceFile::getStatus()
{
	return this->status;
}

const std::string& SourceFile::getCreator()
{
	return this->creator;
}

const std::string& SourceFile::getReviewer()
{
	return this->reviewer;
}

std::string SourceFile::toString()
{
	return this->name + ";" + this->status + ";" + this->creator + ";" + this->reviewer;
}

std::istream& operator>>(std::istream& in, SourceFile& sourceFile)
{
	std::string line, token;
	std::getline(in, line);
	if (line.empty())
		return in;

	std::stringstream ss(line);
	std::vector<std::string> arguments;

	while (std::getline(ss, token, ';'))
		arguments.push_back(token);

	if (arguments.size() != 4)
		return in;

	sourceFile.name = arguments[0];
	sourceFile.status = arguments[1];
	sourceFile.creator = arguments[2];
	sourceFile.reviewer = arguments[3];

	return in;
}
