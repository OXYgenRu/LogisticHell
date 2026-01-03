//
// Created by EgorRychkov on 13.07.2025.
//

#include "GameWorld.h"
#include "../Blueprints/BlueprintLoader.h"

std::shared_ptr<GameWorld>
GameWorld::create(const std::shared_ptr<Node> &parent, EngineContext &ctx, const std::shared_ptr<MainScene> &scene,
                  const std::string &node_id,
                  int render_priority) {
    auto node = std::make_shared<GameWorld>(parent, node_id, render_priority);
    GameWorld::setup(node, ctx, scene);
    parent->add_node(node);
    return node;
}

void
GameWorld::setup(const std::shared_ptr<GameWorld> &node, EngineContext &ctx, const std::shared_ptr<MainScene> &scene) {
    node->extended_world = World::create(node, b2Vec2({0, 0}), 120, "World", 0);

    node->docks_system = DocksSystem::create(node, scene, "DockSystem");
    node->structures_system = StructuresSystem::create(node, node, 0.2, "StructuresSystem");
    node->blueprints_indexer = std::make_shared<BlueprintsIndexer>();
    node->behavior_storage = std::make_shared<UnitsBehaviorStorage>();
    node->blueprint_loader = std::make_shared<BlueprintLoader>(node);
    node->units_system = UnitsSystem::create(node, node, "UnitsSystem");
    node->blocks_system = BlocksSystem::create(node, node, 0.2, "BlocksSystem");
    node->component_system = ComponentsSystem::create(node, node, "ComponentsSystem");
    node->entity_system = EntitySystem::create(node, node, "EntitySystem");
    node->player_system = PlayerSystem::create(node, node, "PlayersSystem");
    node->input_listeners_system = InputListenersSystem::create(node, node, "InputListenersSystem");
    node->player_input_system = PlayerInputSystem::create(node, node, "PlayerInputSystem");
    node->content_packs_system = ContentPacksSystem::create(node, node, "ContentPacksSystem");
    node->values_global_storage = std::make_shared<ValuesGlobalStorage>();
    node->api = std::make_shared<Api>(node, ctx);
}

void GameWorld::open(EngineContext &ctx) {
    this->content_packs_system->load_content_packs(ctx);
    try {
        this->behavior_storage->on_world_open();
    }
    catch (const SystemsExceptions::UnitBehaviorIsNull &e) {
        std::cerr << "[World::open]::UnitBehaviorStorage: behavior of unit '" +
                     blueprints_indexer->get_blueprint_name(e.unit_index()) +
                     "' not found, check behavior loading in content pack.\n";
        exit(0);
    }
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

const std::shared_ptr<BlocksSystem> &GameWorld::get_blocks_system() {
    return blocks_system;
}

const std::shared_ptr<ComponentsSystem> &GameWorld::get_components_system() {
    return component_system;
}

const std::shared_ptr<EntitySystem> &GameWorld::get_entity_system() {
    return entity_system;
}

const std::shared_ptr<PlayerSystem> &GameWorld::get_player_system() {
    return player_system;
}

const std::shared_ptr<InputListenersSystem> &GameWorld::get_input_listeners_system() {
    return input_listeners_system;
}

const std::shared_ptr<PlayerInputSystem> &GameWorld::get_player_input_system() {
    return player_input_system;
}

const std::shared_ptr<ContentPacksSystem> &GameWorld::get_content_packs_system() {
    return content_packs_system;
}

const std::shared_ptr<ValuesGlobalStorage> &GameWorld::get_values_global_storage() {
    return values_global_storage;
}

const std::shared_ptr<Api> &GameWorld::get_api() {
    return api;
}