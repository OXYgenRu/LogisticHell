//
// Created by EgorRychkov on 30.04.2025.
//

#include "Component.h"
#include "../Structure.h"

std::shared_ptr<Component>
Component::create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<Structure> structure,
                  int render_priority,
                  int render_priority_layers) {
    auto node = std::make_shared<Component>(parent, render_priority);
    node->set_render_layers_count(render_priority_layers + 1);
    Component::setup(node, structure);
    parent->add_node(node);
    return node;
}

void Component::setup(std::shared_ptr<Component> node, std::shared_ptr<Structure> structure) {
    node->structure = structure;
    node->grid = ComponentGrid::create(node, node);
}