#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

struct PlatInformation {
	std::string level_name;
	std::string tier;
	std::string tpl_placement;
	std::string pemon_placement;

	std::string to_string();
};
std::ostream & operator<<(std::ostream & os, const PlatInformation & this_);

#define PlatMap std::map<std::string, PlatInformation>