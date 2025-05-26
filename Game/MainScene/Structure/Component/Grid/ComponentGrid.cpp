//
// Created by EgorRychkov on 30.04.2025.
//

#include "ComponentGrid.h"

#include "../Component.h"
#include "../../Structure.h"

std::shared_ptr<ComponentGrid>
ComponentGrid::create(const std::shared_ptr<Node> &parent, std::shared_ptr<Component> component,
                      int render_priority) {
    auto node = std::make_shared<ComponentGrid>(parent, render_priority);
    ComponentGrid::setup(node, component);
    parent->add_node(node);
    return node;
}


void ComponentGrid::setup(std::shared_ptr<ComponentGrid> node, std::shared_ptr<Component> component) {
    auto structure = component->structure.lock();
    node->component = component;
    node->grid_cells.resize(structure->grid->grid_size.y,
                            std::vector<std::shared_ptr<GridCell>>(structure->grid->grid_size.x, nullptr));
}