//
// Created by EgorRychkov on 28.04.2025.
//

#include "Structure.h"

std::shared_ptr<Structure>
Structure::create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<World> world, b2BodyDef &body_def,
                  sf::Vector2i grid_size, float cell_size,
                  int render_priority,
                  int render_priority_layers) {
    auto node = std::make_shared<Structure>(parent, render_priority);
    RigidBody::setup(node, world, body_def, render_priority_layers);
    Structure::setup(node, grid_size, cell_size);
    parent->add_node(node);
    return node;
}

void Structure::setup(std::shared_ptr<Structure> node, sf::Vector2i grid_size, float cell_size) {
    node->grid = Grid::create(node, grid_size, cell_size, node);
}

void Structure::set_block(sf::Vector2i grid_position) {
    if (!this->grid->valid_block_attachment(grid_position)) {
        return;
    }
    this->grid->set_block(grid_position);
}