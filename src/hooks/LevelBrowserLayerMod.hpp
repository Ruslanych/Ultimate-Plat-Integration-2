#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>
#include "../ReloadDialog.hpp"

using namespace geode::prelude;

class $modify(LevelBrowserLayerMod, LevelBrowserLayer) {
	bool init(GJSearchObject* object) {
		if (!LevelBrowserLayer::init(object)) return false;
		
		CCMenuItem* page_menu = (CCMenuItem*) this->getChildByID("page-menu");
		if (page_menu == nullptr) return true;

		CCMenuItemSpriteExtra* buttonBtn = CCMenuItemExt::createSpriteExtraWithFilename(
			"update_btn.png"_spr, 0.4f, [](CCObject* sender){
				ReloadDialog::create()->show();
			});
		page_menu->addChild(buttonBtn);
		page_menu->updateLayout();

		return true;
	}
};