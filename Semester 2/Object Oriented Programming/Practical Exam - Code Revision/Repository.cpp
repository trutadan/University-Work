#include "Repository.h"

void MemberRepository::readFromFile()
{
	std::ifstream fin(this->fileName);

	Member member;
	while (fin >> member)
		this->members.push_back(member);

	fin.close();
}

Member MemberRepository::getMemberByName(const std::string& name)
{
	for (Member member : this->members)
		if (member.getName() == name)
			return member;
}

void MemberRepository::addOneMoreRevisedFile(Member member)
{
	for (int index = 0; index < this->members.size(); index++) {
		Member m = this->members[index];
		if (m.getName() == member.getName()) {
			Member newMember{ member.getName(), member.getNumberOfRevisedFiles() + 1, member.getTotalNumberOfFilesToRevise() };
			this->members[index] = newMember;
			return;
		}
	}
}

std::vector<Member> MemberRepository::getMembersFromRepository()
{
	return this->members;
}

void SourceFileRepository::readFromFile()
{
	std::ifstream fin(this->fileName);

	SourceFile sourceFile;
	while (fin >> sourceFile)
		this->sourceFiles.push_back(sourceFile);

	fin.close();
}

void SourceFileRepository::addNewSourceFile(SourceFile sourceFile)
{
	if (sourceFile.getName().empty())
		throw std::exception("The name is empty!");

	for (SourceFile sFile : this->sourceFiles)
		if (sFile.getName() == sourceFile.getName())
			throw std::exception("Already existing file for given name!");

	this->sourceFiles.push_back(sourceFile);
}

void SourceFileRepository::setRevisedSourceFile(SourceFile sourceFile, std::string name)
{
	for (int index = 0; index < this->sourceFiles.size(); index++) {
		SourceFile sFile = this->sourceFiles[index];
		if (sFile.getName() == sourceFile.getName()) {
			SourceFile newSFile{ sourceFile.getName(), "revised", sourceFile.getCreator(), name };
			this->sourceFiles[index] = newSFile;
			return;
		}
	}
}

std::vector<SourceFile> SourceFileRepository::getSourceFiles()
{
	return this->sourceFiles;
}
