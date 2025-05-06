//
// Created by EgorRychkov on 03.05.2025.
//

#include "BuildingGrid.h"


std::shared_ptr<BuildingGrid>
BuildingGrid::create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<Dock> dock, sf::Vector2f position,
                     float sf_cell_size, float b2_cell_size, sf::Vector2i grid_size,
                     int render_priority,
                     int render_priority_layers) {
    auto node = std::make_shared<BuildingGrid>(parent, render_priority);
    node->set_render_layers_count(render_priority_layers + 1);
    BuildingGrid::setup(node, dock, position, sf_cell_size, b2_cell_size, grid_size);
    parent->add_node(node);
    return node;
}


void BuildingGrid::setup(std::shared_ptr<BuildingGrid> node, std::shared_ptr<Dock> dock, sf::Vector2f position,
                         float sf_cell_size, float b2_cell_size, sf::Vector2i grid_size) {
    node->cells.resize(grid_size.y, std::vector<std::shared_ptr<BuildingBlock>>(grid_size.x));
    node->dock = dock;
    node->position = position;
    node->sf_cell_size = sf_cell_size;
    node->b2_cell_size = b2_cell_size;
    node->grid_size = grid_size;
//    for (int i = 0; i < grid_size.y; i++) {
//        for (int j = 0; j < grid_size.x; j++) {
//            node->cells[i][j] = BuildingBlock::create(node, sf::Vector2i(j, i), sf_cell_size, position);
//        }
//    }
}

void BuildingGrid::clear(EngineContext &ctx) {
    for (int i = 0; i < this->grid_size.y; i++) {
        for (int j = 0; j < this->grid_size.x; j++) {
            this->delete_node(this->cells[i][j]);
        }
    }
    for (int i = 0; i < this->grid_size.y; i++) {
        for (int j = 0; j < this->grid_size.x; j++) {
            this->cells[i][j] = EmptyBlock::create(shared_from_this(), ctx, {j, i}, this->sf_cell_size, this->position);
        }
    }
}

void BuildingGrid::set_block(sf::Vector2i position, int block_id, EngineContext &ctx) {
    this->delete_node(this->cells[position.y][position.x]);
    if (block_id == 1) {
        this->cells[position.y][position.x] = TestConstructionBlock::create(shared_from_this(), ctx, position,
                                                                            this->sf_cell_size, this->position);
    }

}