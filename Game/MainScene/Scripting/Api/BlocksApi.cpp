//
// Created by EgorRychkov on 08.08.2025.
//

#include "BlocksApi.h"
#include "../../World/GameWorld.h"

BlocksApi::BlocksApi(const std::shared_ptr<GameWorld> &world) {
    this->world = world;
}


sf::Vector2f BlocksApi::get_world_point(const unsigned int &block_id, const sf::Vector2f &relative_position) {
    auto block = world.lock()->get_blocks_system()->get_block(block_id);
    std::shared_ptr<Component> component = block->get_weak_component().lock();
    float block_side_size = world.lock()->get_structures_system()->block_side_size;
//
    sf::Vector2f point = {
            relative_position.x * block_side_size + float(block->get_in_component_position().x) * block_side_size,
            relative_position.y * block_side_size + float(block->get_in_component_position().y) * block_side_size};
    b2Vec2 b2_point = b2Body_GetWorldPoint(component->rigid_body->body_id, {point.x, point.y});
    return {b2_point.x, b2_point.y};
}