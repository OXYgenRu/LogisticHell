//
// Created by EgorRychkov on 10.05.2025.
//

#ifndef LOGISTICHELL_BLUEPRINTLOADER_H
#define LOGISTICHELL_BLUEPRINTLOADER_H

#include "memory"
#include "Blueprint/Blueprint.h"
#include "BlueprintsIndexer.h"
#include "../Scripting/UnitsBehaviorStorage.h"

class GameWorld;

class BlueprintLoader {
public:
    using blueprint_loader = std::function<std::shared_ptr<Blueprint>(int rotation)>;

    explicit BlueprintLoader(const std::shared_ptr<GameWorld> &world);

    void register_structure(const std::string &structure_name, Blueprint template_blueprint);

    void
    register_unit(const std::string &unit_name, Blueprint template_blueprint,
                  const std::shared_ptr<UnitProperties> &properties, const std::shared_ptr<UnitBehavior> &behavior);

    std::vector<unsigned int> &get_all_blueprints();

    std::vector<unsigned int> &get_all_units();

    std::shared_ptr<Blueprint> create_blueprint(const unsigned int &blueprint_index, int rotation);

private:
    void register_blueprint(const std::string &blueprint_name, Blueprint template_blueprint);

    std::weak_ptr<GameWorld> world;

    std::unordered_map<unsigned int, blueprint_loader> loaders;
    std::vector<unsigned int> blueprints;
    std::vector<unsigned int> structures;
    std::vector<unsigned int> units;

};


#endif //LOGISTICHELL_BLUEPRINTLOADER_H
