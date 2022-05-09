#pragma once
#include <vector>
#include <string>
class Sensor
{
public:
	Sensor();

	Sensor(const std::string& _producer, std::vector<double> recordings);

	virtual bool sendAlert() = 0;

	virtual double getPrice() = 0;

	virtual std::string toString();

	std::string getProducer();

	~Sensor();

protected:
	std::string producer;
	std::vector<double> recordings;
};

