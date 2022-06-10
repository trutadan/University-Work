#pragma once
#include "FileRepository.h"

class TextFileRepository : public FileRepository
{
public:
	TextFileRepository();

	TextFileRepository(const std::string& _file_name);

	~TextFileRepository() override;

private:
	void read_from_file() override;

	void save_to_file() override;
};

