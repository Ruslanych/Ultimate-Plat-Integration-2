#pragma once

#include <Geode/Geode.hpp>

#include "ReloadDialog.hpp"

using namespace geode::prelude;
class DataLoader {
private:
	static std::shared_ptr<DataLoader> instance;
	TaskHolder<web::WebResponse> task_holder;
	bool init;
	matjson::Value query_data;
	DataLoader();
	static std::shared_ptr<DataLoader> get_instance();
public:
	static void load_data(ReloadDialog* reload_layer = nullptr);
};
