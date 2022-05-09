#pragma once
#include "../Domain/Event.h"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

void strip(std::string& string);

std::vector<std::string> split(const std::string& string, char delimitator);

bool strcasecmp(const std::string& first_string, const std::string& second_string);

bool check_sooner_event(const Event& first_event, const Event& second_event);