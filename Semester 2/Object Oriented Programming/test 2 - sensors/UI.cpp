#include "UI.h"

UI::UI()
{
	{}
}

UI::UI(Device _device)
{
	this->device = _device;
}

void UI::addSensor()
{
	std::string producer;
	std::cout << "Enter the name of the producer: ";
	std::cin >> producer;

	int recordingsNumber;
	std::cout << "Enter the number of recordings: ";
	std::cin >> recordingsNumber;

	std::vector<double> recordings;
	double recording;
	for (int i = 0; i < recordingsNumber; i++) {
		std::cout << "Enter recording: ";
		std::cin >> recording;
		recordings.push_back(recording);
	}

	std::string sensorType;
	std::cout << "Enter the name of the sensor type: ";
	std::cin >> sensorType;

	Sensor* sensor;

	if (sensorType == "temperature") {
		double diameter;
		std::cout << "Enter the diameter of the sensor: ";
		std::cin >> diameter;

		double length;
		std::cout << "Enter the length of the sensor: ";
		std::cin >> length;

		auto temperatureSensor = new TemperatureSensor( producer, recordings, diameter, length );
		sensor = temperatureSensor;
		this->device.addSensor(sensor);
		std::cout << "The sensor has been added!\n";
	}

	else if (sensorType == "Humidity") {
		auto humiditySensor = new HumiditySensor(producer, recordings);
		sensor = humiditySensor;
		this->device.addSensor(sensor);
		std::cout << "The sensor has been added!\n";
	}

	else if (sensorType == "Smoke"){
		auto smokeSensor = new SmokeSensor(producer, recordings);
		sensor = smokeSensor;
		this->device.addSensor(sensor);
		std::cout << "The sensor has been added!\n";
	}
	
	else {
		std::cout << "Bad input provided!\n";
		return;
	}
}

void UI::showAllSensors()
{
	std::cout << "All sensors: \n";
	
	for (auto& sensor : this->device.getAllSensors())
		std::cout << sensor->toString() << "\n";

	std::cout << "\n";
}

void UI::showAlertingSensors()
{
	std::cout << "All alerting sensors: \n";

	for (auto& sensor : this->device.getAlertingSensors())
		std::cout << sensor->toString() << "\n";

	std::cout << "\n";
}

void UI::saveToFile()
{
	std::string fileName;
	std::cout << "Enter the name of the file: ";
	std::cin >> fileName;

	this->device.writeToFile(fileName);
	std::cout << "The file has been completed!\n";

	std::cout << "\n";
}

void UI::populateDevicesList()
{
	Sensor* sensor;

	std::vector<double> sensors;
	sensors.push_back(35);
	sensors.push_back(44);
	sensors.push_back(80);
	sensors.push_back(71);

	auto temperatureSensor = new TemperatureSensor("A", sensors, 5, 50);
	sensor = temperatureSensor;
	this->device.addSensor(sensor);

	auto humiditySensor = new HumiditySensor("C", sensors);
	sensor = humiditySensor;
	this->device.addSensor(sensor);

	auto smokeSensor = new SmokeSensor("B", sensors);
	sensor = smokeSensor;
	this->device.addSensor(sensor);
}

void printMenu()
{
	std::cout << "1. Add new sensor.\n";
	std::cout << "2. Display all sensors.\n";
	std::cout << "3. Display alerting sensors.\n";
	std::cout << "4. Save to file.\n";
	std::cout << "5. Exit.\n";
}

void UI::runProgram()
{
	int command;

	populateDevicesList();

	while (true) {
		printMenu();
		std::cout << "> ";
		std::cin >> command;
		switch (command) {
		case 1:
			this->addSensor();
			break;

		case 2:
			this->showAllSensors();
			break;

		case 3:
			this->showAlertingSensors();
			break;

		case 4:
			this->saveToFile();
			break;

		case 5:
			return;

		default:
			std::cout << "Not a valid option!\n";
			break;

		}
	}
}

UI::~UI()
{
	{}
}
