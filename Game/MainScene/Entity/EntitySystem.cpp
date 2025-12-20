//
// Created by EgorRychkov on 07.11.2025.
//

#include "EntitySystem.h"
#include "../World/GameWorld.h"

std::shared_ptr<EntitySystem>
EntitySystem::create(const std::shared_ptr<Node> &parent, const std::shared_ptr<GameWorld> &world,
                     const std::string &node_id,
                     int render_priority) {
    auto node = std::make_shared<EntitySystem>(parent, node_id, render_priority);
    EntitySystem::setup(node, world);
    parent->add_node(node);
    return node;
}


void EntitySystem::setup(const std::shared_ptr<EntitySystem> &node, const std::shared_ptr<GameWorld> &world) {
    node->world = world;
}


std::shared_ptr<Entity>
EntitySystem::spawn(EngineContext &ctx, const sf::Vector2f &b2_position, const sf::Vector2f &b2_size,
                    const float &density,
                    const float &friction) {
    unsigned int new_entity_id = this->max_entity_id++;
    auto entity = Entity::create(world.lock(), ctx, world.lock(), new_entity_id, b2_position, b2_size, density,
                                 friction,
                                 "Entity" + std::to_string(new_entity_id));
    this->entities[new_entity_id] = entity;
    return entity;
}
