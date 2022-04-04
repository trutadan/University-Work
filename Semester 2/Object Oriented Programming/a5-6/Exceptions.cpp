#include "Exceptions.h"

ValueError::ValueError(const char* message) {
	this->error_message = message;
}

const char* ValueError::what() const noexcept {
	return this->error_message;
}

RepositoryError::RepositoryError(const char* message)
{
	this->error_message = message;
}

const char* RepositoryError::what() const noexcept
{
	return this->error_message;
}

ListError::ListError(const char* message)
{
	this->error_message = message;

}

const char* ListError::what() const noexcept
{
	return this->error_message;
}
