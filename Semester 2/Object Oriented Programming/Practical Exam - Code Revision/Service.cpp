#include "Service.h"

void Service::addNewSourceFile(SourceFile sourceFile)
{
	this->fileRepository.addNewSourceFile(sourceFile);
	this->notify();
}

void Service::setSourceFileRevised(SourceFile sourceFile, std::string name)
{
	this->fileRepository.setRevisedSourceFile(sourceFile, name);
	this->notify();
}

void Service::setOneMoreFileRevised(Member member)
{
	this->memberRepository.addOneMoreRevisedFile(member);
	this->notify();
}

Member Service::getMemberByName(const std::string& name)
{
	return this->memberRepository.getMemberByName(name);
}

std::vector<Member> Service::getMembers()
{
	return this->memberRepository.getMembersFromRepository();
}

std::vector<SourceFile> Service::getSourceFiles()
{
	return this->fileRepository.getSourceFiles();
}

std::vector<SourceFile> Service::getSortedSourceFiles()
{
	std::vector<SourceFile> sortedSourceFiles = this->getSourceFiles();

	std::sort(sortedSourceFiles.begin(), sortedSourceFiles.end(), [](SourceFile& f1, SourceFile& f2) { return f1.getName() < f2.getName(); });

	return sortedSourceFiles;
}
