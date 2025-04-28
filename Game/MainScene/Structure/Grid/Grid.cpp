//
// Created by EgorRychkov on 28.04.2025.
//

#include "Grid.h"
#include "GridViewer.h"

std::shared_ptr<Grid>
Grid::create(std::shared_ptr<ContainerNode> parent, sf::Vector2i grid_size, float cell_size,
             std::shared_ptr<RigidBody> rigid_body,
             int render_priority,
             int render_priority_layers) {
    auto node = std::make_shared<Grid>(parent, render_priority);
    node->set_render_layers_count(render_priority_layers + 1);
    Grid::setup(node, grid_size, cell_size, rigid_body);
    parent->add_node(node);
    return node;
}

void Grid::setup(std::shared_ptr<Grid> node, sf::Vector2i grid_size, float cell_size,
                 std::shared_ptr<RigidBody> &structure) {
    node->structure = structure;
    node->blocks.resize(grid_size.y, std::vector<std::shared_ptr<BaseBlock>>(grid_size.x, nullptr));
    node->grid_view.resize(grid_size.y, std::vector<std::shared_ptr<GridViewer>>(grid_size.x, nullptr));
    node->grid_view_layer = ContainerNode::create(node);
    node->cell_size = cell_size;

    for (int i = 0; i < grid_size.y; i++) {
        for (int j = 0; j < grid_size.x; j++) {
            node->grid_view[i][j] = GridViewer::create(node->grid_view_layer, node, b2Vec2({float(i), float(j)}),
                                                       node->cell_size);
        }
    }
}

void Grid::set_block(std::shared_ptr<BaseBlock> &block) {
    this->blocks[block->grid_position.y][block->grid_position.x] = block;
}