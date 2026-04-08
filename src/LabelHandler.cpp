#include "LabelHandler.hpp"

LabelHandler::LabelHandler() {
    this->platformer_map = std::shared_ptr<PlatMap>(new std::map<std::string, PlatInformation>());
}

std::shared_ptr<LabelHandler> LabelHandler::get_instance() {
    if (!LabelHandler::instance)
    LabelHandler::instance = std::shared_ptr<LabelHandler> (new LabelHandler());
    return LabelHandler::instance;
}

void LabelHandler::level_cell_moveNextToView(LevelCell* level_cell, CCNode* node) {  // Almost direct copy from cvolton.compact-lists
    if(!node) return;

    auto viewButton = level_cell->m_mainMenu->getChildByID("view-button");
    if(!viewButton) return;

    /*node->setPositionX(viewButton->getPositionX() - viewButton->getScaledContentSize().width - 5 - node->getScaledContentSize().width / 2);
    node->setPositionY(viewButton->getPositionY());

    node->setPosition(m_mainLayer->convertToNodeSpace(m_mainMenu->convertToWorldSpace(node->getPosition())));*/
    node->setPosition({276, 25});
    //node->setPosition({276 - (node->getScaledContentSize().width / 2), 25});
}

std::shared_ptr<PlatMap> LabelHandler::get_plat_map() {
    return LabelHandler::get_instance()->platformer_map;
}

std::string LabelHandler::get_tier_sprite(std::string tier_string) {
    if (tier_string == "-")  return "tier_moon_icon_NA.png"_spr;
    if (tier_string == "P")  return "tier_moon_icon_P.png"_spr;
    if (tier_string == "0")  return "tier_moon_icon_T0.png"_spr;
    if (tier_string == "1")  return "tier_moon_icon_T1.png"_spr;
    if (tier_string == "2")  return "tier_moon_icon_T2.png"_spr;
    if (tier_string == "3")  return "tier_moon_icon_T3.png"_spr;
    if (tier_string == "4")  return "tier_moon_icon_T4.png"_spr;
    if (tier_string == "5")  return "tier_moon_icon_T5.png"_spr;
    if (tier_string == "6")  return "tier_moon_icon_T6.png"_spr;
    if (tier_string == "7")  return "tier_moon_icon_T7.png"_spr;
    if (tier_string == "8")  return "tier_moon_icon_T8.png"_spr;
    if (tier_string == "9")  return "tier_moon_icon_T9.png"_spr;
    if (tier_string == "10") return "tier_moon_icon_T10.png"_spr;
    if (tier_string == "11") return "tier_moon_icon_T11.png"_spr;
    if (tier_string == "12") return "tier_moon_icon_T12.png"_spr;
    if (tier_string == "13") return "tier_moon_icon_T13.png"_spr;
    if (tier_string == "14") return "tier_moon_icon_T14.png"_spr;
    if (tier_string == "15") return "tier_moon_icon_T15.png"_spr;
    if (tier_string == "16") return "tier_moon_icon_T16.png"_spr;
    if (tier_string == "17") return "tier_moon_icon_T17.png"_spr;
    if (tier_string == "18") return "tier_moon_icon_T18.png"_spr;
    if (tier_string == "19") return "tier_moon_icon_T19.png"_spr;
    if (tier_string == "20") return "tier_moon_icon_T20.png"_spr;
    return "tier_moon_icon_NA.png"_spr;
}

void LabelHandler::draw_plat_info_layer(CCNode* plat_info_layer, GJGameLevel* level, LevelCell* level_cell) {
    bool is_compact_mode = level_cell->m_compactView;

    CCNode* ref;

    std::shared_ptr<PlatMap> map = LabelHandler::get_plat_map();

    std::string level_id = fmt::format("{}", level->m_levelID.value());

    CCSprite* tpl_sprite = CCSprite::create("tpl.png"_spr);
    tpl_sprite->setID("tpl-sprite"_spr);
    CCLabelBMFont* tpl_label = CCLabelBMFont::create("", "goldFont.fnt");
    tpl_label->setID("tpl-label"_spr);
    tpl_label->setAnchorPoint({0, 0.5});
    CCSprite* pemon_sprite = CCSprite::create("pemon.png"_spr);
    pemon_sprite->setID("pemon-sprite"_spr);
    CCLabelBMFont* pemon_label = CCLabelBMFont::create("", "bigFont.fnt");
    pemon_label->setAnchorPoint({0, 0.5});
    pemon_label->setID("pemon-label"_spr);
    if (!is_compact_mode) {
        tpl_sprite->setPositionX(298);
        tpl_sprite->setPositionY(22);
        tpl_sprite->setScale(0.3);
        tpl_label->setPositionX(306);
        tpl_label->setPositionY(23);
        tpl_label->setScale(0.45);
        pemon_sprite->setPositionX(298);
        pemon_sprite->setPositionY(8);
        pemon_sprite->setScale(0.3);
        pemon_label->setPositionX(306);
        pemon_label->setPositionY(8);
        pemon_label->setScale(0.35);
    } else {
        tpl_sprite->setPositionX(248);
        tpl_sprite->setPositionY(29);
        tpl_sprite->setScale(0.25);
        tpl_label->setPositionX(254.5);
        tpl_label->setPositionY(30);
        tpl_label->setScale(0.35);
        pemon_sprite->setPositionX(248);
        pemon_sprite->setPositionY(18);
        pemon_sprite->setScale(0.25);
        pemon_label->setPositionX(254.5);
        pemon_label->setPositionY(19);
        pemon_label->setScale(0.27);
    }

    if (map->contains(level_id)) {
        if (Mod::get()->getSettingValue<bool>("hide-aredl")
        && (ref = level_cell->getChildByID("main-layer"))
        && (ref = ref->getChildByID("hiimjustin000.integrated_demonlist/level-rank-label")))
            ref->setVisible(false);
        tpl_label->setString(map->at(level_id).tpl_placement.c_str());
        pemon_label->setString(map->at(level_id).pemon_placement.c_str());
        CCSprite* tier_icon = CCSprite::create(LabelHandler::get_tier_sprite(map->at(level_id).tier).c_str());
        if (!is_compact_mode) {
            tier_icon->setPositionX(340);
            tier_icon->setPositionY(15);
            tier_icon->setScale(0.9);
        } else {
            tier_icon->setPositionX(281.25);
            tier_icon->setPositionY(24);
            tier_icon->setScale(0.75);
            if (level->m_listPosition == 0
            && (ref = level_cell->m_mainLayer->getChildByID("completed-icon"))) {  // Cvolton :: CompactLists Detection
                LabelHandler::level_cell_moveNextToView(level_cell, ref);
                ref->setPositionX(ref->getPositionX() - 41.f);
            }
        }
        tier_icon->setID("tier-icon"_spr);
        plat_info_layer->addChild(tier_icon);
    } else {
        tpl_sprite->setVisible(false);
        pemon_sprite->setVisible(false);
    }

    plat_info_layer->addChild(tpl_sprite);
    plat_info_layer->addChild(tpl_label);
    plat_info_layer->addChild(pemon_sprite);
    plat_info_layer->addChild(pemon_label);
}

void LabelHandler::redraw_all_layers() {
    CCNode* ref;
    if (!(ref = CCScene::get())) return;
    if (!(ref = ref->getChildByIDRecursive("LevelCell"))) return;
    if (!(ref = ref->getParent())) return;
    CCArray* layers = ref->getChildren();
    for (CCNode* node : CCArrayExt<CCNode*>(layers)) {
        LevelCell* level_cell;
        if (!(level_cell = typeinfo_cast<LevelCell*>(node))) continue;
        CCNode* plat_info_layer;
        if (!(plat_info_layer = level_cell->getChildByIDRecursive("plat-integration-layer"_spr))) continue;
        plat_info_layer->removeAllChildren();
        LabelHandler::draw_plat_info_layer(plat_info_layer, level_cell->m_level, level_cell);
    }
}
std::shared_ptr<LabelHandler> LabelHandler::instance;