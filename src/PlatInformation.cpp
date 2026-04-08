#include "PlatInformation.hpp"

std::string PlatInformation::to_string() {
    return fmt::format("{} : tier {}, tpl #{}, pemon #{}", this->level_name, this->tier, this->tpl_placement, this->pemon_placement);
};
std::ostream & operator<<(std::ostream & os, const PlatInformation & this_) {
	return (os << this_.level_name << " : tier " << this_.tier << ", tpl " << this_.tpl_placement << ", pemon " << this_.pemon_placement);
};

#define PlatMap std::map<std::string, PlatInformation>

std::string to_string(PlatMap pm) {
	std::string result = "PlatMap object\n";
	for (std::pair<std::string, PlatInformation> pair : pm)
		result += fmt::format("  pm[{}] = {}\n", pair.first, pair.second.to_string());
	return result;
}