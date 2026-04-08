#include <Geode/Geode.hpp>

using namespace geode::prelude;
#include <Geode/utils/web.hpp>
#include <arc/prelude.hpp>
#include <Geode/loader/Event.hpp>

#include "ReloadDialog.hpp"
#include "DataLoader.hpp"
#include "LabelHandler.hpp"
#include "hooks/LevelCellMod.hpp"
#include "hooks/LevelBrowserLayerMod.hpp"

$execute {
	DataLoader::load_data();
}
