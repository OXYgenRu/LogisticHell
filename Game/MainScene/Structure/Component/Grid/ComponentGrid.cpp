//
// Created by EgorRychkov on 30.04.2025.
//

#include "ComponentGrid.h"

#include "../Component.h"
#include "../../Structure.h"

std::shared_ptr<ComponentGrid>
ComponentGrid::create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<Component> component,
                      int render_priority,
                      int render_priority_layers) {
    auto node = std::make_shared<ComponentGrid>(parent, render_priority);
    node->set_render_layers_count(render_priority_layers + 1);
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