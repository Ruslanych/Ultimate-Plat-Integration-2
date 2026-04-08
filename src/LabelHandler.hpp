#pragma once

#include <Geode/Geode.hpp>
#include "PlatInformation.hpp"

using namespace geode::prelude;

class LabelHandler {
private:
	static std::shared_ptr<LabelHandler> instance;
	std::shared_ptr<PlatMap> platformer_map;
	LabelHandler();
	static std::shared_ptr<LabelHandler> get_instance();
public:
	static std::shared_ptr<PlatMap> get_plat_map();
	static std::string get_tier_sprite(std::string tier_string);
	static void draw_plat_info_layer(CCNode* plat_info_layer, GJGameLevel* level, LevelCell* level_cell);
	static void redraw_all_layers();
};