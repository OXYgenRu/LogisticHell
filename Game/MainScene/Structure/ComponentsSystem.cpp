//
// Created by EgorRychkov on 04.08.2025.
//

#include "ComponentsSystem.h"
#include "../World/GameWorld.h"

std::shared_ptr<ComponentsSystem>
ComponentsSystem::create(const std::shared_ptr<Node> &parent, const std::shared_ptr<GameWorld> &world,
                         const std::string &node_id,
                         int render_priority) {
    auto node = std::make_shared<ComponentsSystem>(parent, node_id, render_priority);
    ComponentsSystem::setup(node, world);
    parent->add_node(node);
    return node;
}


void ComponentsSystem::setup(const std::shared_ptr<ComponentsSystem> &node, const std::shared_ptr<GameWorld> &world) {
    node->world = world;
}

std::shared_ptr<Component> ComponentsSystem::create_component(const std::shared_ptr<Structure> &structure) {
    unsigned int new_component_id = this->max_component_id++;
    std::shared_ptr<Component> new_component = Component::create(world.lock(), structure, new_component_id,
                                                                 "StructureComponent");
    this->components[new_component_id] = new_component;
    return new_component;
}


void ComponentsSystem::destroy_component(const std::shared_ptr<Component> &component) {
    this->delete_component(component);
    for (int y = 0; y < component->grid_size.y; y++) {
        for (int x = 0; x < component->grid_size.x; x++) {
            if (component->blocks[y][x] != nullptr) {
                world.lock()->get_blocks_system()->delete_block(component->blocks[y][x]);
                auto unit = component->blocks[y][x]->get_weak_unit().lock();
                for (auto &to: component->blocks[y][x]->get_render_quads()) {
                    unit->delete_render_feature(to->get_feature_name());
                }
                unit->delete_block(component->blocks[y][x]->get_in_component_position());
            }
        }
    }
    world.lock()->delete_node(component);
    world.lock()->get_world()->delete_node(component->rigid_body);
    component->structure.lock()->delete_component(component);
}

void ComponentsSystem::delete_component(const std::shared_ptr<Component> &component) {
    auto it = this->components.find(component->get_component_id());
    if (it == this->components.end()) {
        throw std::runtime_error("Deleting component not found");
    }
    this->components.erase(it);
}