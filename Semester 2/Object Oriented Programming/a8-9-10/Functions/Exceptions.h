#pragma once
#include <exception>

class ValueError : public std::exception {
public:
	explicit ValueError(const char* message);

	const char* what() const noexcept override;

private:
	const char* error_message;
};

class RepositoryError : public std::exception {
public:
	explicit RepositoryError(const char* message);
	
	const char* what() const noexcept override;

private:
	const char* error_message;
};

class ListError : public std::exception {
public:
	explicit ListError(const char* message);

	const char* what() const noexcept override;

private:
	const char* error_message;
};

class FileError : public std::exception {
public:
	explicit FileError(const char* message);

	const char* what() const noexcept override;

private:
	const char* error_message;
};