//
// Created by EgorRychkov on 28.07.2025.
//

#include "UnitsSystem.h"
#include "../World/GameWorld.h"

std::shared_ptr<UnitsSystem>
UnitsSystem::create(const std::shared_ptr<Node> &parent, const std::shared_ptr<GameWorld> &world,
                    const std::string &node_id,
                    int render_priority) {
    auto node = std::make_shared<UnitsSystem>(parent, node_id, render_priority);
    UnitsSystem::setup(node, world);
    parent->add_node(node);
    return node;
}

void UnitsSystem::setup(const std::shared_ptr<UnitsSystem> &node, const std::shared_ptr<GameWorld> &world) {
    node->world = world;
}

std::shared_ptr<Unit> UnitsSystem::create_unit(const sf::Vector2i &position, int rotation,
                                               const unsigned int &unit_index) {
    std::cout << "Unit created" << '\n';
    units[max_unit_id] = Unit::create(world.lock(), position, rotation, unit_index, max_unit_id);
    max_unit_id++;
    return units[max_unit_id - 1];
}

std::shared_ptr<Unit> UnitsSystem::get_unit(const unsigned int &unit_id) {
    auto it = this->units.find(unit_id);
    if (it == this->units.end()) {
        return nullptr;
    }
    return it->second;
}

void UnitsSystem::update(EngineContext &ctx) {
    auto locked_world = world.lock();
    for (auto &to: units) {
        locked_world->get_behavior_storage()->get_unit_behavior(
                to.second->get_unit_index())->update(to.first,
                                                     ctx.last_frame_delta_time,
                                                     *locked_world->get_api());

    }
}