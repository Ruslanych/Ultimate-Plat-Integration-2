#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelCell.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>
#include <Geode/utils/web.hpp>
#include <arc/prelude.hpp>
#include <Geode/loader/Event.hpp>

#include "ReloadDialog.hpp"
#include "DataLoader.hpp"
#include "LabelHandler.hpp"

$execute {
	DataLoader::load_data();
}

class $modify(LevelCellMod, LevelCell) {
	static void onModify(auto& self) {
		(void) self.setHookPriorityAfterPost("LevelCell::loadCustomLevelCell", "cvolton.compact_lists");
	}

	struct Fields {
		CCNode* plat_info_layer;
		TaskHolder<void> task_holder;
	};
	
	void loadCustomLevelCell() {
		LevelCell::loadCustomLevelCell();
		if (!this->m_level || !this->m_level->isPlatformer() || 
			this->m_level->m_levelType == GJLevelType::Main ||
			this->m_level->m_levelType == GJLevelType::Editor)
			return;

		CCNode* main_layer = this->getChildByID("main-layer");
		if (!main_layer) return;
		
		CCNode* ref;
		if ((ref = main_layer->getChildByID("xboctatuk.globallistpositions/gdl-icon")) != nullptr)
			ref->setVisible(false);
		if ((ref = main_layer->getChildByID("xboctatuk.globallistpositions/gdl-label")) != nullptr)
			ref->setVisible(false);
		
		CCNode* plat_info_layer = CCNode::create();
		plat_info_layer->setID("plat-integration-layer"_spr);
		LabelHandler::draw_plat_info_layer(plat_info_layer, this->m_level, this);
		
		main_layer->addChild(plat_info_layer);
	}

	void moveNextToView(CCNode* node) {  // Direct copy from cvolton.compact-lists
		if(!node) return;

		auto viewButton = m_mainMenu->getChildByID("view-button");
		if(!viewButton) return;

		/*node->setPositionX(viewButton->getPositionX() - viewButton->getScaledContentSize().width - 5 - node->getScaledContentSize().width / 2);
		node->setPositionY(viewButton->getPositionY());

		node->setPosition(m_mainLayer->convertToNodeSpace(m_mainMenu->convertToWorldSpace(node->getPosition())));*/
		node->setPosition({276, 25});
		//node->setPosition({276 - (node->getScaledContentSize().width / 2), 25});
	}
};

class $modify(LevelBrowserLayerMod, LevelBrowserLayer) {
	bool init(GJSearchObject* object) {
		if (!LevelBrowserLayer::init(object)) return false;
		
		CCMenuItem* page_menu = (CCMenuItem*) this->getChildByID("page-menu");
		if (page_menu == nullptr) return true;

		CCMenuItemSpriteExtra* buttonBtn = CCMenuItemExt::createSpriteExtraWithFilename(
			"update_btn.png"_spr, 0.5f, [](CCObject* sender){
				ReloadDialog::create()->show();
			});
		page_menu->addChild(buttonBtn);
		page_menu->updateLayout();

		return true;
	}
};