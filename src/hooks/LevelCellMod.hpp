#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/LevelCell.hpp>
#include "../LabelHandler.hpp"

using namespace geode::prelude;

class $modify(LevelCellMod, LevelCell) {
	static void onModify(auto& self) {
		(void) self.setHookPriorityAfterPost("LevelCell::loadFromLevel", "cvolton.compact_lists");
		(void) self.setHookPriorityAfterPost("LevelCell::loadFromLevel", "xboctatuk.globallistpositions");
		(void) self.setHookPriorityAfterPost("LevelCell::loadFromLevel", "hiimjustin000.integrated_demonlist");
	}

	struct Fields {
		CCNode* plat_info_layer;
		TaskHolder<void> task_holder;
	};
	
	void loadFromLevel(GJGameLevel* level) {
		LevelCell::loadFromLevel(level);
		if (!level || !level->isPlatformer() || 
			level->m_levelType == GJLevelType::Main ||
			level->m_levelType == GJLevelType::Editor)
			return;

		CCNode* main_layer = this->getChildByID("main-layer");
		if (!main_layer) return;
		
		if (Mod::get()->getSettingValue<bool>("hide-global-list")) {
			CCNode* ref;
			if ((ref = main_layer->getChildByID("xboctatuk.globallistpositions/gdl-icon")) != nullptr)
			ref->setVisible(false);
			if ((ref = main_layer->getChildByID("xboctatuk.globallistpositions/gdl-label")) != nullptr)
			ref->setVisible(false);
		}
		CCNode* plat_info_layer = CCNode::create();
		plat_info_layer->setID("plat-integration-layer"_spr);
		LabelHandler::draw_plat_info_layer(plat_info_layer, level, this);
		
		main_layer->addChild(plat_info_layer);
	}
};
