#pragma once

#include <Geode/Geode.hpp> 

using namespace geode::prelude;

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