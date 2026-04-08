#include "DataLoader.hpp"

#include "PlatInformation.hpp"
#include "LabelHandler.hpp"

std::vector<matjson::Value> NULL_VECTOR(0);

DataLoader::DataLoader() { this->init = false; }
	
std::shared_ptr<DataLoader> DataLoader::get_instance() {
    if (!DataLoader::instance)
    DataLoader::instance = std::shared_ptr<DataLoader> (new DataLoader());
    return DataLoader::instance;
}

void DataLoader::load_data(ReloadDialog* reload_layer) {
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
                    reload_layer->update_progress_screen(2);
                    reload_layer->working = false;
                }
            }
        }
    );
};
std::shared_ptr<DataLoader> DataLoader::instance;
