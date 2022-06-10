#pragma once
#include <string>
#include <sstream>
class Member
{
private:
	std::string name;
	int numberOfRevisedFiles;
	int totalNumberOfFilesToRevise;

public:
	Member() = default;

	Member(const std::string& _name, const int& _umberOfRevisedFiles, const int& _totalNumberOfFilesToRevise);

	const std::string& getName();

	const int& getNumberOfRevisedFiles();

	void setNumberOfRevisedFiles(const int& number);

	const int& getTotalNumberOfFilesToRevise();

	friend std::istream& operator>>(std::istream& reader, Member& member);
};

