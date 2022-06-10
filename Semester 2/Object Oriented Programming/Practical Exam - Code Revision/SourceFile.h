#pragma once
#include <string>
#include <sstream>
#include <vector>
class SourceFile
{
private:
	std::string name;
	std::string status;
	std::string creator;
	std::string reviewer;

public:
	SourceFile() = default;

	SourceFile(const std::string& _name, const std::string& _status, const std::string& _creator, const std::string& _reviewer);

	const std::string& getName();

	const std::string& getStatus();

	const std::string& getCreator();

	const std::string& getReviewer();

	std::string toString();

	friend std::istream& operator>>(std::istream& reader, SourceFile& sourceFile);
};

