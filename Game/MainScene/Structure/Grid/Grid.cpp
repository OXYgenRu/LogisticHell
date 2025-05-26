//
// Created by EgorRychkov on 28.04.2025.
//

#include <iostream>
#include "Grid.h"


std::shared_ptr<Grid>
Grid::create(const std::shared_ptr<Node> &parent, sf::Vector2i grid_size, float cell_size,
             std::shared_ptr<Structure> rigid_body,
             int render_priority,
             int render_priority_layers) {
    auto node = std::make_shared<Grid>(parent, render_priority);
    Grid::setup(node, grid_size, cell_size, rigid_body);
    parent->add_node(node);
    return node;
}

void Grid::setup(std::shared_ptr<Grid> node, sf::Vector2i grid_size, float cell_size,
                 std::shared_ptr<Structure> &structure) {
    node->structure = structure;
    node->cell_size = cell_size;
    node->grid_size = grid_size;
    node->grid_cells.resize(grid_size.y, std::vector<std::shared_ptr<GridCell>>(grid_size.x, nullptr));
    node->grid_view_layer = Node::create(node);

    for (int i = 0; i < grid_size.y; i++) {
        for (int j = 0; j < grid_size.x; j++) {
            node->grid_cells[i][j] = GridCell::create(node->grid_view_layer, structure, node, sf::Vector2i({j, i}),
                                                       cell_size);
        }
    }
}

//bool Grid::valid_block_attachment(sf::Vector2i grid_position) {
//    if (grid_position.y < 0 || grid_position.y >= blocks.size()) {
//        std::cout << "Block attachment rejected y < 0 or y >= grid y size. x: " << grid_position.x << " y: "
//                  << grid_position.y << std::endl;
//        return false;
//    }
//    if (grid_position.x < 0 || grid_position.x >= blocks[0].size()) {
//        std::cout << "Block attachment rejected x < 0 or x >= grid x size. x: " << grid_position.x << " y: "
//                  << grid_position.y << std::endl;
//        return false;
//    }
//    if (this->blocks[grid_position.y][grid_position.x] != nullptr) {
//        std::cout << "Block attachment rejected, grid cell not free. x:" << grid_position.x << " y: "
//                  << grid_position.y << std::endl;
//        return false;
//    }
//    return true;
//}
//
//void Grid::set_block(sf::Vector2i grid_position) {
//    this->blocks[grid_position.y][grid_position.x] = BaseBlock::create(shared_from_this(), this->structure.lock(),
//                                                                       b2Vec2({float(grid_position.x),
//                                                                               float(grid_position.y)}),
//                                                                       this->cell_size);
//}