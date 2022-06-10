#pragma once
#include "Repository.h"
#include "Observer.h"
#include <algorithm>

class Service : public Subject
{
private:
	MemberRepository memberRepository;
	SourceFileRepository fileRepository;

public:
	Service() = default;

	Service(MemberRepository& _memberRepository, SourceFileRepository& _fileRepository) : memberRepository(_memberRepository), fileRepository(_fileRepository) { this->memberRepository.readFromFile(); this->fileRepository.readFromFile(); };

	void addNewSourceFile(SourceFile sourceFile);

	void setSourceFileRevised(SourceFile sourceFile, std::string name);

	void setOneMoreFileRevised(Member member);

	Member getMemberByName(const std::string& name);

	std::vector<Member> getMembers();

	std::vector<SourceFile> getSourceFiles();

	std::vector<SourceFile> getSortedSourceFiles();
};

