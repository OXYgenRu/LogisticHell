//
// Created by EgorRychkov on 28.04.2025.
//

#include <iostream>
#include "Grid.h"
#include "GridViewer.h"


std::shared_ptr<Grid>
Grid::create(std::shared_ptr<ContainerNode> parent, sf::Vector2i grid_size, float cell_size,
             std::shared_ptr<Structure> rigid_body,
             int render_priority,
             int render_priority_layers) {
    auto node = std::make_shared<Grid>(parent, render_priority);
    node->set_render_layers_count(render_priority_layers + 1);
    Grid::setup(node, grid_size, cell_size, rigid_body);
    parent->add_node(node);
    return node;
}

void Grid::setup(std::shared_ptr<Grid> node, sf::Vector2i grid_size, float cell_size,
                 std::shared_ptr<Structure> &structure) {
    node->structure = structure;
    node->blocks.resize(grid_size.y, std::vector<std::shared_ptr<BaseBlock>>(grid_size.x, nullptr));
    node->grid_view.resize(grid_size.y, std::vector<std::shared_ptr<GridViewer>>(grid_size.x, nullptr));
    node->grid_view_layer = ContainerNode::create(node);
    node->grid_collider = GridCollider::create(node, node);
    node->grid_collider->b2_vertices[0] = {-cell_size / 2,
                                           cell_size / 2 + + (grid_size.y - 1) * cell_size};
    node->grid_collider->b2_vertices[1] = {(grid_size.x - 1) * cell_size + cell_size / 2,
                                           cell_size / 2 + (grid_size.y - 1) * cell_size};
    node->grid_collider->b2_vertices[2] = {(grid_size.x - 1) * cell_size + cell_size / 2,
                                           -cell_size / 2};
    node->grid_collider->b2_vertices[3] = {-cell_size / 2,
                                           -cell_size / 2};
    node->cell_size = cell_size;

    for (int i = 0; i < grid_size.y; i++) {
        for (int j = 0; j < grid_size.x; j++) {
            node->grid_view[i][j] = GridViewer::create(node->grid_view_layer, node, b2Vec2({float(i), float(j)}),
                                                       node->cell_size);
        }
    }
}

bool Grid::valid_block_attachment(sf::Vector2i grid_position) {
    if (grid_position.y < 0 || grid_position.y >= blocks.size()) {
        std::cout << "Block attachment rejected y < 0 or y >= grid y size. x: " << grid_position.x << " y: "
                  << grid_position.y << std::endl;
        return false;
    }
    if (grid_position.x < 0 || grid_position.x >= blocks[0].size()) {
        std::cout << "Block attachment rejected x < 0 or x >= grid x size. x: " << grid_position.x << " y: "
                  << grid_position.y << std::endl;
        return false;
    }
    if(this->blocks[grid_position.y][grid_position.x] != nullptr){
        std::cout << "Block attachment rejected, grid cell not free. x:" << grid_position.x << " y: "
                  << grid_position.y << std::endl;
        return false;
    }
    return true;
}

void Grid::set_block(sf::Vector2i grid_position) {
    this->blocks[grid_position.y][grid_position.x] = BaseBlock::create(shared_from_this(), this->structure.lock(),
                                                                       b2Vec2({float(grid_position.x),
                                                                               float(grid_position.y)}),
                                                                       this->cell_size);
}