#pragma once
#include "Controller.h"
class UI
{
private:
	Controller controller;

public:
	UI(const Controller& _c) : controller(_c) {};

	void show_all_patients();

	void remove_patient_ui(const std::string& name);
	
	void start_program();
};

