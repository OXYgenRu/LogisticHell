//
// Created by EgorRychkov on 10.05.2025.
//

#ifndef LOGISTICHELL_BLUEPRINTLOADER_H
#define LOGISTICHELL_BLUEPRINTLOADER_H

#include "memory"
#include "Blueprint/Blueprint.h"

class BlueprintLoader {
public:
    using blueprint_loader = std::function<std::shared_ptr<Blueprint>(int rotation)>;

    void register_structure(const std::string &structure_id, Blueprint template_blueprint);

    void
    register_unit(const std::string &unit_id, Blueprint template_blueprint, const std::shared_ptr<UnitProperties> &properties);


    std::vector<std::string> &get_all_blueprints();

    std::vector<std::string> &get_all_units();

    std::shared_ptr<Blueprint> create_blueprint(const std::string &blueprint_id, int rotation);

private:
    void register_blueprint(const std::string &blueprint_id, Blueprint template_blueprint);

    std::unordered_map<std::string, blueprint_loader> loaders;
    std::vector<std::string> blueprints;
    std::vector<std::string> structures;
    std::vector<std::string> units;
};


#endif //LOGISTICHELL_BLUEPRINTLOADER_H
