#include "ReloadDialog.hpp"

#include "DataLoader.hpp"

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