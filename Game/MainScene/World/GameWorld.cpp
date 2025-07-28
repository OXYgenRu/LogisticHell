//
// Created by EgorRychkov on 13.07.2025.
//

#include "GameWorld.h"
#include "../Blueprints/BlueprintLoader.h"

std::shared_ptr<GameWorld>
GameWorld::create(const std::shared_ptr<Node> &parent, const std::shared_ptr<MainScene> &scene,
                  const std::string &node_id,
                  int render_priority) {
    auto node = std::make_shared<GameWorld>(parent, node_id, render_priority);
    GameWorld::setup(node, scene);
    parent->add_node(node);
    return node;
}

void GameWorld::setup(const std::shared_ptr<GameWorld> &node, const std::shared_ptr<MainScene> &scene) {
    node->extended_world = World::create(node, b2Vec2({0, 0}), 120, "World", 0);

    node->docks_system = DocksSystem::create(node, scene, "DockSystem");
    node->structures_system = StructuresSystem::create(node, node, 0.2, "StructuresSystem");
    node->blueprints_indexer = std::make_shared<BlueprintsIndexer>();
    node->behavior_storage = std::make_shared<UnitsBehaviorStorage>();
    node->blueprint_loader = std::make_shared<BlueprintLoader>(node);
    node->units_system = UnitsSystem::create(node, node, "UnitsSystem");
    node->api = std::make_shared<Api>(node);
}

const std::shared_ptr<World> &GameWorld::get_world() {
    return extended_world;
}

const float &GameWorld::get_pixel_per_meter() {
    return extended_world->pixel_per_meter;
}

const b2WorldId &GameWorld::get_world_id() {
    return extended_world->world_id;
}

const std::shared_ptr<StructuresSystem> &GameWorld::get_structures_system() {
    return structures_system;
}

const std::shared_ptr<DocksSystem> &GameWorld::get_docks_system() {
    return docks_system;
}

const std::shared_ptr<BlueprintLoader> &GameWorld::get_blueprints_loader() {
    return blueprint_loader;
}

const std::shared_ptr<BlueprintsIndexer> &GameWorld::get_blueprints_indexer() {
    return blueprints_indexer;
}

const std::shared_ptr<UnitsBehaviorStorage> &GameWorld::get_behavior_storage() {
    return behavior_storage;
}

const std::shared_ptr<UnitsSystem> &GameWorld::get_units_system() {
    return units_system;
}

const std::shared_ptr<Api> &GameWorld::get_api() {
    return api;
}