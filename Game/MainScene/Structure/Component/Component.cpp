//
// Created by EgorRychkov on 30.04.2025.
//

#include "Component.h"
#include "../Structure.h"

std::shared_ptr<Component>
Component::create(const std::shared_ptr<Node> &parent, std::shared_ptr<Structure> structure,
                  int render_priority,
                  int render_priority_layers) {
    auto node = std::make_shared<Component>(parent, render_priority);
    Component::setup(node, structure);
    parent->add_node(node);
    return node;
}

void Component::setup(std::shared_ptr<Component> node, std::shared_ptr<Structure> structure) {
    node->structure = structure;
    node->grid = ComponentGrid::create(node, node);
}