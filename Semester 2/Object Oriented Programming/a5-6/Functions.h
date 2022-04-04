#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "Event.h"

void strip(std::string&);

std::vector<std::string> split(const std::string&, char);

bool strcasecmp(const std::string&, const std::string&);

bool check_sooner_event(const Event&, const Event&);