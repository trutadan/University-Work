#pragma once
#include "FileRepository.h"

class CSVRepository : public FileRepository
{
public:
	CSVRepository();

	CSVRepository(const std::string& _file_name);

	~CSVRepository() override;

private:
	void read_from_file() override;

	void save_to_file() override;
};