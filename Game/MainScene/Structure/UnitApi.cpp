//
// Created by EgorRychkov on 01.07.2025.
//

#include "UnitApi.h"
#include "StructuresSystem.h"
#include "Unit.h"
#include "../MainScene.h"

sf::Vector2i get_grid_vector(const sf::Vector2i &vector, int rotation) {
    switch (rotation % 4) {
        case 0:
            return {vector.x, vector.y};
        case 1:
            return {vector.y, -vector.x};
        case 2:
            return {-vector.x, -vector.y};
        case 3:
            return {-vector.y, vector.x};
    }
    return vector;
}

sf::Vector2f get_force_vector(const sf::Vector2f &vector, int rotation) {
    switch (rotation % 4) {
        case 0:
            return {vector.x, vector.y};
        case 1:
            return {vector.y, -vector.x};
        case 2:
            return {-vector.x, -vector.y};
        case 3:
            return {-vector.y, vector.x};
    }
    return vector;
}


UnitApi::UnitApi(const std::shared_ptr<Unit> &unit) {
    this->weak_unit = unit;
}

UnitApi::UnitApi() {
}


void UnitApi::apply_force(const sf::Vector2i &block_position, const sf::Vector2f &relative_position,
                          const sf::Vector2f &force) {

    auto unit = this->weak_unit.lock();
    sf::Vector2i relative_block_position = get_grid_vector(block_position, unit->get_rotation()) + unit->get_position();
    std::shared_ptr<ComponentBlock> block = unit->get_block(relative_block_position);
    if (block == nullptr) {
        return;
    }
    std::shared_ptr<Component> component = block->get_component();
    float block_side_size = unit->scene.lock()->structures_system->block_side_size;

    sf::Vector2f force_point = {float(relative_block_position.x) * block_side_size,
                                float(relative_block_position.y) * block_side_size};
    force_point += {relative_position.x * block_side_size,
                    relative_position.y * block_side_size};
    b2Vec2 b2_force_point = b2Body_GetWorldPoint(component->rigid_body->body_id, {force_point.x, force_point.y});
    sf::Vector2f world_force = get_force_vector(force, unit->get_rotation());
    world_force = {world_force.x, -world_force.y};
    world_force = component->get_transformable().getTransform().transformPoint(world_force) -
                  component->get_transformable().getTransform().transformPoint({0.f, 0.f});
    b2Body_ApplyForce(component->rigid_body->body_id, {world_force.x, -world_force.y}, b2_force_point, true);
}