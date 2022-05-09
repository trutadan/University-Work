#pragma once
#include <iostream>
#include "Device.h"

class UI
{
public:
	UI();

	UI(Device _device);

	void addSensor();

	void showAllSensors();

	void showAlertingSensors();

	void saveToFile();

	void populateDevicesList();

	void runProgram();

	~UI();

private:
	Device device;
};

