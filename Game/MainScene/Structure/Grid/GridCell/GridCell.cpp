//
// Created by EgorRychkov on 01.05.2025.
//

#include "GridCell.h"
#include "../../../../../Engine/Nodes/Base/ContainerNode.h"
#include "../../Structure.h"

std::shared_ptr<GridCell> GridCell::create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<Structure> structure,
                                           std::shared_ptr<Grid> grid,
                                           sf::Vector2i grid_position, float cell_size,
                                           int render_priority,
                                           int render_priority_layers) {
    auto node = std::make_shared<GridCell>(parent, render_priority);
    node->set_render_layers_count(render_priority_layers + 1);
    GridCell::setup(node, structure, grid, grid_position, cell_size);
    parent->add_node(node);
    return node;
}

void GridCell::setup(std::shared_ptr<GridCell> node, std::shared_ptr<Structure> structure, std::shared_ptr<Grid> grid,
                     sf::Vector2i grid_position, float cell_size) {
    node->structure = structure;

    node->vertices.resize(4);

    auto world = structure->world.lock();
    float sf_cell_size = cell_size * world->pixel_per_meter;
    sf::Vector2f quad_position = {float(grid_position.x) * sf_cell_size, float(grid_position.y) * sf_cell_size};

    node->vertices[0] = sf::Vector2f(
            structure->position.x + quad_position.x - sf_cell_size / 2,
            structure->position.y - quad_position.y + sf_cell_size / 2);
    node->vertices[1] = sf::Vector2f(
            structure->position.x + quad_position.x - sf_cell_size / 2,
            structure->position.y - quad_position.y - sf_cell_size / 2);
    node->vertices[2] = sf::Vector2f(
            structure->position.x + quad_position.x + sf_cell_size / 2,
            structure->position.y - quad_position.y - sf_cell_size / 2);
    node->vertices[3] = sf::Vector2f(
            structure->position.x + quad_position.x + sf_cell_size / 2,
            structure->position.y - quad_position.y + sf_cell_size / 2);

    node->textured_quad = TexturedQuad::create(node);
//    node->textured_quad->set_texture("blocks/EmptyGridBlockBlue.png");
    node->textured_quad->set_quad(node->vertices);
}