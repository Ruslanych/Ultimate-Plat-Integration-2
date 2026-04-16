#include <Geode/Geode.hpp>

using namespace geode::prelude;
#include <Geode/utils/web.hpp>
#include <arc/prelude.hpp>
#include <Geode/loader/Event.hpp>

#include "ReloadDialog.hpp"
#include "DataLoader.hpp"
#include "LabelHandler.hpp"
#include "hooks/LevelCell.hpp"
#include "hooks/LevelBrowserLayer.hpp"
#include "hooks/LevelInfoLayer.hpp"

$execute {
	DataLoader::load_data();
}

class $modify(LevelCell) {
    static void onModify(auto& self) {
        if (!self.setHookPriorityPost("LevelCell::loadFromLevel", Priority::Late)) {
            geode::log::warn("Failed to set hook priority.");
        }
    }
};
