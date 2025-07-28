//
// Created by EgorRychkov on 13.07.2025.
//

#ifndef LOGISTICHELL_GAMEWORLD_H
#define LOGISTICHELL_GAMEWORLD_H


#include "../../../Engine/Nodes/Base/Node.h"
#include "../Structure/StructuresSystem.h"
#include "../Dock/DocksSystem.h"
#include "../Blueprints/BlueprintsIndexer.h"
#include "../Scripting/UnitsBehaviorStorage.h"
#include "../Structure/UnitsSystem.h"

class GameWorld : public Node {
private:
    std::shared_ptr<World> extended_world;
    std::shared_ptr<StructuresSystem> structures_system;
    std::shared_ptr<DocksSystem> docks_system;
    std::shared_ptr<BlueprintsIndexer> blueprints_indexer;
    std::shared_ptr<UnitsBehaviorStorage> behavior_storage;
    std::shared_ptr<BlueprintLoader> blueprint_loader;
    std::shared_ptr<UnitsSystem> units_system;
    std::shared_ptr<Api> api;
public:
    static std::shared_ptr<GameWorld>
    create(const std::shared_ptr<Node> &parent, const std::shared_ptr<MainScene> &scene, const std::string &node_id,
           int render_priority = 0);

    explicit GameWorld(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0)
            : Node(parent, node_id,
                   render_priority) {}

    static void setup(const std::shared_ptr<GameWorld> &node, const std::shared_ptr<MainScene> &scene);

    const std::shared_ptr<World> &get_world();

    const float &get_pixel_per_meter();

    const b2WorldId &get_world_id();

    const std::shared_ptr<StructuresSystem> &get_structures_system();

    const std::shared_ptr<DocksSystem> &get_docks_system();

    const std::shared_ptr<BlueprintLoader> &get_blueprints_loader();

    const std::shared_ptr<BlueprintsIndexer> &get_blueprints_indexer();

    const std::shared_ptr<UnitsBehaviorStorage> &get_behavior_storage();

    const std::shared_ptr<UnitsSystem> &get_units_system();

    const std::shared_ptr<Api> &get_api();
};


#endif //LOGISTICHELL_GAMEWORLD_H
