#include <Geode/Geode.hpp>

#include <Geode/modify/LevelInfoLayer.hpp>

class $modify(LevelInfoLayerMod, LevelInfoLayer) {
    static void onModify(auto& self) {
        (void) self.setHookPriorityAfterPost("LevelInfoLayer::init", "b1rtek.gddlintegration");
    }

    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge)) return false;

        if (!Mod::get()->getSettingValue<bool>("enable-mod")) return true;
        if (!Mod::get()->getSettingValue<bool>("enable-levelinfolayer")) return true;
        
        if (!level || !level->isPlatformer() || 
			level->m_levelType == GJLevelType::Main ||
			level->m_levelType == GJLevelType::Editor)
			return true;
        CCNode* ref;
        if ((ref = this->getChildByID("b1rtek.gddlintegration/rating-menu")))
            ref->setVisible(false);
        
        CCPoint diff_face_position = m_difficultySprite->getPosition();
        CCSize diff_face_size = m_difficultySprite->getContentSize();
        
        CCNode* plat_info_layer = CCNode::create();
		plat_info_layer->setID("plat-integration-layer"_spr);
        plat_info_layer->setPositionX(diff_face_position.x - diff_face_size.width / 2);
        plat_info_layer->setPositionY(diff_face_position.y - diff_face_size.height / 3.2f);
        // plat_info_layer->setPositionX(diff_face_position.x - 50);
        // plat_info_layer->setPositionY(diff_face_position.y);
        
        LabelHandler::draw_plat_info_layer(plat_info_layer, level, nullptr, this);
		
		this->addChild(plat_info_layer);
		
        // "b1rtek.gddlintegration/rating-menu";
        return true;
    }
};