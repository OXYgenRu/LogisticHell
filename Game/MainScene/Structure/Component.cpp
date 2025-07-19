//
// Created by EgorRychkov on 11.06.2025.
//

#include "Component.h"
#include "Structure.h"
#include "../../../Engine/Application.h"

std::shared_ptr<Component>
Component::create(const std::shared_ptr<Node> &parent, const std::shared_ptr<Structure> &structure,
                  const std::string &node_id,
                  int render_priority) {
    std::shared_ptr<Component> node = std::make_shared<Component>(parent, node_id, render_priority);
    Component::setup(node, structure);
    parent->add_node(node);
    return node;
}

void Component::setup(std::shared_ptr<Component> &node, const std::shared_ptr<Structure> &structure) {
    node->structure = structure;
    node->grid_size = structure->blueprint->grid_size;
    node->collision_blocks.resize(node->grid_size.y,
                                  std::vector<std::shared_ptr<CollisionPolygon>>(node->grid_size.x));
    node->blocks.resize(node->grid_size.y,
                        std::vector<std::shared_ptr<ComponentBlock>>(node->grid_size.x));
    node->colliders.resize(node->grid_size.y,
                           std::vector<std::shared_ptr<UI::Collider>>(node->grid_size.x));
}

void Component::update(EngineContext &ctx) {
    this->set_position(this->rigid_body->get_position());
    this->set_rotation(this->rigid_body->get_rotation());
    this->set_origin(this->rigid_body->get_origin());
}


Component::~Component() {
    std::cout << "Component destroyed" << '\n';
}