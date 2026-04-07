#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelCell.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>
#include <Geode/utils/web.hpp>
#include <arc/prelude.hpp>
#include <Geode/loader/Event.hpp>

// int cache_size_limit = 100;
// int cache_size_cut = 21;

// struct PlatInformation {
// 	int tpl_placement;
// 	int pemon_placement;
// 	int tier;
// };

// class Cache {
// 	private:
	
// 	static std::shared_ptr<Cache> instance;
// 	int size;
// 	std::vector<SeedValueRSV> keys;  // level_id-s
// 	std::vector<PlatInformation> values;
	
// 	Cache(int size, std::vector<SeedValueRSV> keys, std::vector<PlatInformation> values) {
// 		this->size = size;
// 		this->keys = keys;
// 		this->values = values;
// 	}
	
// 	static std::shared_ptr<Cache> get_instance() {
// 		std::shared_ptr<Cache> instance = Cache::get_instance();
// 		if (Cache::instance == nullptr)
// 		Cache::instance = std::shared_ptr<Cache> (new Cache(0, std::vector<SeedValueRSV>(), std::vector<PlatInformation>()));
// 		return Cache::instance;
// 	}
	
// 	public:
	
// 	static PlatInformation find(SeedValueRSV key) {
// 		std::shared_ptr<Cache> instance = Cache::get_instance();
// 		for (int i = 0; i < instance->size; i++) {
// 			if (instance->keys[i] == key) return instance->values[i];
// 		}
// 		return {" - ", " - ", -1};
// 	}
	
// 	static void push(SeedValueRSV key, PlatInformation value) {
// 		std::shared_ptr<Cache> instance = Cache::get_instance();
// 		instance->keys.push_back(key);
// 		instance->values.push_back(value);
// 		if (++instance->size >= cache_size_limit) {
// 			instance->keys.erase(instance->keys.begin(), instance->keys.begin() + cache_size_cut);
// 			instance->size -= cache_size_limit;
// 		}
// 	}
// };


std::vector<matjson::Value> NULL_VECTOR(0);

struct PlatInformation {
	std::string level_name;
	std::string tier;
	std::string tpl_placement;
	std::string pemon_placement;

	std::string to_string() {
		return fmt::format("{} : tier {}, tpl #{}, pemon #{}", this->level_name, this->tier, this->tpl_placement, this->pemon_placement);
	};
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

class LabelHandler {
private:

	static std::shared_ptr<LabelHandler> instance;
	std::shared_ptr<PlatMap> platformer_map;

	LabelHandler() {
		this->platformer_map = std::shared_ptr<PlatMap>(new std::map<std::string, PlatInformation>());
	}
	
	static std::shared_ptr<LabelHandler> get_instance() {
		if (LabelHandler::instance == nullptr)
		LabelHandler::instance = std::shared_ptr<LabelHandler> (new LabelHandler());
		return LabelHandler::instance;
	}
	
public:

	static std::shared_ptr<PlatMap> get_plat_map() {
		return LabelHandler::get_instance()->platformer_map;
	}

	static std::string get_tier_sprite(std::string tier_string) {
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

	static void draw_plat_info_layer(CCNode* plat_info_layer, GJGameLevel* level, LevelCell* level_cell) {
		bool is_compact_mode = level_cell->m_compactView;

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

		// cvolton detection
		if (is_compact_mode && level->m_listPosition == 0 && level_cell && level_cell->m_mainLayer->getChildByID("completed-icon")) {
			level_cell->m_mainLayer->getChildByID("completed-icon")->setPositionX(level_cell->m_mainLayer->getChildByID("completed-icon")->getPositionX() - 41.f);
		}
	}

	static void redraw_all_layers() {
		CCNode* ref;
		if ((ref = CCScene::get()) == nullptr) return;
		if ((ref = ref->getChildByIDRecursive("LevelCell")) == nullptr) return;
		if ((ref = ref->getParent()) == nullptr) return;
		CCArray* layers = ref->getChildren();
		for (CCNode* node : CCArrayExt<CCNode*>(layers)) {
			LevelCell* level_cell;
			if ((level_cell = typeinfo_cast<LevelCell*>(node)) == nullptr) continue;
			CCNode* plat_info_layer;
			if ((plat_info_layer = level_cell->getChildByIDRecursive("plat-integration-layer"_spr)) == nullptr) continue;
			plat_info_layer->removeAllChildren();
			LabelHandler::draw_plat_info_layer(plat_info_layer, level_cell->m_level, level_cell);
		}
	}
};
std::shared_ptr<LabelHandler> LabelHandler::instance;

class ReloadDialog : public geode::Popup {
protected:
	bool init() override;
	void execute(CCObject* sender);
public:
	bool working;
	void keyBackClicked() override;
	void onClose(CCObject* sender) override;
	static ReloadDialog* create();
	void update_progress_screen(int code);
};

class DataLoader {
private:
	static std::shared_ptr<DataLoader> instance;
	TaskHolder<web::WebResponse> task_holder;
	bool init;
	matjson::Value query_data;

	DataLoader() { this->init = false; }
	
	static std::shared_ptr<DataLoader> get_instance() {
		if (DataLoader::instance == nullptr)
		DataLoader::instance = std::shared_ptr<DataLoader> (new DataLoader());
		return DataLoader::instance;
	}
	
public:
	
	static void load_data(ReloadDialog* reload_layer = nullptr) {
		auto req = web::WebRequest();
		log::debug("Loading data from the sheet ...");
        DataLoader::get_instance()->task_holder.spawn(
			"Get query",
			req.get("https://sheets.googleapis.com/v4/spreadsheets/13rpmCGCC8NKvRJhVcUuxixUdEuc_I6rm9LlwgB2HAsM/values/'Levels'!A2:E?key=AIzaSyAVpBERRc97KM9PNu_sv5q6BEQ7ccUlxac"),
            [reload_layer](web::WebResponse res) {
				if (res.ok()) {
					std::shared_ptr<PlatMap> map = LabelHandler::get_plat_map();
					map->clear();
					
					matjson::Value query_data = res.json().unwrapOr(matjson::Value());
					std::vector<matjson::Value> values = query_data["values"].asArray().unwrapOr(NULL_VECTOR);
					int size = values.size();
					
					log::debug("Data load successful - {} rows. Converting to the PlatMap format ...", size);
					for (int i = 0; i < size; i++) {
						matjson::Value tuple = values[i].asArray().unwrapOr(NULL_VECTOR);
						switch (tuple.size())
						if (tuple.size() == 0) continue;
						std::string id = tuple[0].asString().unwrapOr("ERR");
						if (id == "ERR") continue;
						
						std::string level_name = "-";
						std::string tier = "-";
						std::string tpl_placement = "-";
						std::string pemon_placement = "-";
						if (tuple.size() > 1) level_name      = tuple[1].asString().unwrapOr("-");
						if (tuple.size() > 2) tier            = tuple[2].asString().unwrapOr("-");
						if (tuple.size() > 3) tpl_placement   = tuple[3].asString().unwrapOr("-");
						if (tuple.size() > 4) pemon_placement = tuple[4].asString().unwrapOr("-");
						
						map->insert_or_assign(id, PlatInformation({level_name, tier, tpl_placement, pemon_placement}));
					}
					log::debug("Data convertion successful");
					
					LabelHandler::redraw_all_layers();

					
					if (reload_layer != nullptr) {
						LabelHandler::redraw_all_layers();
						reload_layer->update_progress_screen(1);
						reload_layer->working = false;
					}
				} else {
					if (reload_layer != nullptr) {
						LabelHandler::redraw_all_layers();
						reload_layer->update_progress_screen(2);
						reload_layer->working = false;
					}
				}
            }
        );
	}
};
std::shared_ptr<DataLoader> DataLoader::instance;

bool ReloadDialog::init() {
	if (!Popup::init(240.f, 120.f)) return false;
	
	this->setTitle("Data reload");
	this->working = false;
	
	CCLabelBMFont* label_main = CCLabelBMFont::create("Update data for\nplat integration?", "bigFont.fnt");
	label_main->setPosition(15.f, 65.f);
	label_main->setScale(0.65);
	label_main->setAnchorPoint(CCPointMake(0.f, 0.5f));
	label_main->setAlignment(CCTextAlignment::kCCTextAlignmentLeft);
	label_main->setID("label-main"_spr);
	this->m_mainLayer->addChild(label_main);
	
	CCMenuItemSpriteExtra* button_yes = CCMenuItemSpriteExtra::create(
		ButtonSprite::create("Yes", 1.f), this, menu_selector(ReloadDialog::execute)
	);
	button_yes->setPosition(60, 25);
	button_yes->setID("yes-button"_spr);
	this->m_buttonMenu->addChild(button_yes);

	CCMenuItemSpriteExtra* button_exit = CCMenuItemSpriteExtra::create(
		ButtonSprite::create("Exit", 1.f), this, menu_selector(ReloadDialog::onClose)
	);
	button_exit->setPosition(60.f, 25.f);
	button_exit->setID("exit-button"_spr);
	button_exit->setVisible(false);
	this->m_buttonMenu->addChild(button_exit);

		LoadingSpinner* loading_spinner = LoadingSpinner::create(25.f);
		loading_spinner->setPosition(60.f, 25.f);
		// loading_circle->ignoreAnchorPointForPosition(true);
		loading_spinner->setID("loading-spinner"_spr);
		// loading_circle->setVisible(false);
		this->m_mainLayer->addChild(loading_spinner);
		
		CCLabelBMFont* label_running = CCLabelBMFont::create("Processing\nrequest...", "bigFont.fnt");
		label_running->setPosition(15.f, 65.f);
		label_running->setScale(0.65);
		label_running->setAnchorPoint(CCPointMake(0.f, 0.5f));
		label_running->setAlignment(CCTextAlignment::kCCTextAlignmentLeft);
		label_running->setID("label-running"_spr);
		label_running->setVisible(false);
		this->m_mainLayer->addChild(label_running);

		CCLabelBMFont* label_success = CCLabelBMFont::create("Data update\nsuccessful!", "bigFont.fnt");
		label_success->setPosition(15.f, 65.f);
		label_success->setScale(0.65);
		label_success->setAnchorPoint(CCPointMake(0.f, 0.5f));
		label_success->setAlignment(CCTextAlignment::kCCTextAlignmentLeft);
		label_success->setID("label-success"_spr);
		label_success->setVisible(false);
		this->m_mainLayer->addChild(label_success);

		CCLabelBMFont* label_fail = CCLabelBMFont::create("Data update\nfailed", "bigFont.fnt");
		label_fail->setPosition(15.f, 65.f);
		label_fail->setScale(0.65);
		label_fail->setAnchorPoint(CCPointMake(0.f, 0.5f));
		label_fail->setAlignment(CCTextAlignment::kCCTextAlignmentLeft);
		label_fail->setID("label-success"_spr);
		label_fail->setVisible(false);
		this->m_mainLayer->addChild(label_fail);
	
	return true;
}

void ReloadDialog::keyBackClicked() {
	log::debug("keyBackClicked : {}, {}", this->working, this);
	if (!this->working)
	geode::Popup::keyBackClicked();
};

void ReloadDialog::execute(CCObject* sender) {
	this->working = true;
	this->update_progress_screen(0);
	DataLoader::load_data(this);
}

void ReloadDialog::onClose(CCObject* sender) {
	if (!this->working)
	geode::Popup::onClose(sender);
}

ReloadDialog* ReloadDialog::create() {
	auto ret = new ReloadDialog();
	if (ret->init()) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

void ReloadDialog::update_progress_screen(int code) {
	CCNode* ref;
	CCNode* ref2;
	if (code == 0) {
		ref = this->m_buttonMenu;
			ref->setVisible(false);
		if ((ref = this->m_buttonMenu->getChildByID("yes-button"_spr)) != nullptr)
			ref->setVisible(false);
		if ((ref = this->m_mainLayer->getChildByID("label-main"_spr)) != nullptr)
			ref->setVisible(false);
		if ((ref = this->m_mainLayer->getChildByID("label-running"_spr)) != nullptr)
			ref->setVisible(true);
		if ((ref = this->m_mainLayer->getChildByID("loading-spinner"_spr)) != nullptr)
			ref->setVisible(true);
	} else if (code == 1) {
		this->m_buttonMenu->setVisible(true);
		if ((ref = this->m_mainLayer->getChildByID("label-running"_spr)) != nullptr)
			ref->setVisible(false);
		if ((ref = this->m_mainLayer->getChildByID("loading-spinner"_spr)) != nullptr)
			ref->setVisible(false);
		if ((ref = this->m_mainLayer->getChildByID("label-success"_spr)) != nullptr)
			ref->setVisible(true);
		if ((ref = this->m_buttonMenu->getChildByID("exit-button"_spr)) != nullptr)
			ref->setVisible(true);
	} else if (code == 2) {
		this->m_buttonMenu->setVisible(true);
		if ((ref = this->m_mainLayer->getChildByID("label-running"_spr)) != nullptr)
			ref->setVisible(false);
		if ((ref = this->m_mainLayer->getChildByID("loading-spinner"_spr)) != nullptr)
			ref->setVisible(false);
		if ((ref = this->m_mainLayer->getChildByID("label-fail"_spr)) != nullptr)
			ref->setVisible(true);
		if ((ref = this->m_buttonMenu->getChildByID("exit-button"_spr)) != nullptr)
			ref->setVisible(true);
	}
}
$execute {
	DataLoader::load_data();
}

class $modify(LevelCellPRI, LevelCell) {
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
		if (main_layer == nullptr) return;
		
		CCNode* plat_info_layer = CCNode::create();
		plat_info_layer->setID("plat-integration-layer"_spr);
		LabelHandler::draw_plat_info_layer(plat_info_layer, this->m_level, this);
		
		main_layer->addChild(plat_info_layer);
	}
};

class $modify(LevelBrowserLayerPRI, LevelBrowserLayer) {
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