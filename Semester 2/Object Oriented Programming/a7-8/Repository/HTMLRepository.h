#pragma once
#include "FileRepository.h"

class HTMLRepository : public FileRepository
{
public:
	HTMLRepository();

	HTMLRepository(const std::string& _file_name);

	~HTMLRepository() override;

private:
	void read_from_file() override;

	void save_to_file() override;
};
