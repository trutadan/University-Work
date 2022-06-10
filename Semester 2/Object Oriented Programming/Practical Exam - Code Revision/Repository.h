#pragma once
#include <vector>
#include <fstream>
#include "Member.h"
#include "SourceFile.h"

class MemberRepository {
private:
	std::vector<Member> members;
	std::string fileName;

public:
	MemberRepository(const std::string& _fileName = "members.txt") : fileName(_fileName) {};

	void readFromFile();

	Member getMemberByName(const std::string& name);
	
	void addOneMoreRevisedFile(Member member);

	std::vector<Member> getMembersFromRepository();
};

class SourceFileRepository {
private:
	std::vector<SourceFile> sourceFiles;
	std::string fileName;

public:
	SourceFileRepository(const std::string& _fileName = "sourcefiles.txt") : fileName(_fileName) {};

	void readFromFile();

	void addNewSourceFile(SourceFile sourceFile);

	void setRevisedSourceFile(SourceFile sourceFile, std::string name);

	std::vector<SourceFile> getSourceFiles();
};