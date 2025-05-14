//
// Created by EgorRychkov on 03.05.2025.
//

#include "BuildingGrid.h"


std::shared_ptr<BuildingGrid>
BuildingGrid::create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<Dock> dock, sf::Vector2f position,
                     float sf_cell_size, float b2_cell_size, sf::Vector2i grid_size,
                     std::shared_ptr<BlockFactory> block_factory,
                     int render_priority,
                     int render_priority_layers) {
    auto node = std::make_shared<BuildingGrid>(parent, render_priority);
    node->set_render_layers_count(render_priority_layers + 1);
    BuildingGrid::setup(node, dock, position, sf_cell_size, b2_cell_size, grid_size, block_factory);
    parent->add_node(node);
    return node;
}


void BuildingGrid::setup(std::shared_ptr<BuildingGrid> node, std::shared_ptr<Dock> dock, sf::Vector2f position,
                         float sf_cell_size, float b2_cell_size, sf::Vector2i grid_size,
                         std::shared_ptr<BlockFactory> block_factory) {
    node->cells_layer = ContainerNode::create(node, 0);
    node->preview_cells_layer = ContainerNode::create(node, 1);
    node->mask_cells_layer = ContainerNode::create(node, 2);
    node->cells.resize(grid_size.y, std::vector<std::shared_ptr<BuildingBlock>>(grid_size.x));
    node->preview_cells.resize(grid_size.y, std::vector<std::shared_ptr<BuildingBlock>>(grid_size.x));
    node->mask_cells.resize(grid_size.y, std::vector<std::shared_ptr<BuildingBlock>>(grid_size.x));
    node->dock = dock;
    node->position = position;
    node->sf_cell_size = sf_cell_size;
    node->b2_cell_size = b2_cell_size;
    node->grid_size = grid_size;
    node->block_factory = block_factory;
}

void BuildingGrid::clear(EngineContext &ctx) {
    for (int i = 0; i < this->grid_size.y; i++) {
        for (int j = 0; j < this->grid_size.x; j++) {
            this->cells_layer->delete_node(this->cells[i][j]);
        }
    }
    for (int i = 0; i < this->grid_size.y; i++) {
        for (int j = 0; j < this->grid_size.x; j++) {
            this->cells[i][j] = this->block_factory->create_block("empty_block::empty_block", this->cells_layer, ctx,
                                                                  {j, i},
                                                                  this->sf_cell_size, this->position, 0);
        }
    }
}


void BuildingGrid::clear_preview(EngineContext &ctx) {
    for (int i = 0; i < this->grid_size.y; i++) {
        for (int j = 0; j < this->grid_size.x; j++) {
            this->preview_cells_layer->delete_node(this->preview_cells[i][j]);
        }
    }
    for (int i = 0; i < this->grid_size.y; i++) {
        for (int j = 0; j < this->grid_size.x; j++) {
            this->preview_cells[i][j] = this->block_factory->create_block("void_block::void_block",
                                                                          this->preview_cells_layer,
                                                                          ctx,
                                                                          {j, i},
                                                                          this->sf_cell_size, this->position, 0);
        }
    }
}

void BuildingGrid::clear_mask(EngineContext &ctx) {
    for (int i = 0; i < this->grid_size.y; i++) {
        for (int j = 0; j < this->grid_size.x; j++) {
            this->mask_cells_layer->delete_node(this->mask_cells[i][j]);
        }
    }
    for (int i = 0; i < this->grid_size.y; i++) {
        for (int j = 0; j < this->grid_size.x; j++) {
            this->mask_cells[i][j] = this->block_factory->create_block("void_block::void_block",
                                                                       this->mask_cells_layer,
                                                                       ctx,
                                                                       {j, i},
                                                                       this->sf_cell_size, this->position, 0);
        }
    }
}

void BuildingGrid::set_block(sf::Vector2i position, std::string block_id, int rotation, EngineContext &ctx) {
    this->cells_layer->delete_node(this->cells[position.y][position.x]);

    this->cells[position.y][position.x] = this->block_factory->create_block(block_id,
                                                                            this->cells_layer, ctx,
                                                                            {position.x, position.y},
                                                                            this->sf_cell_size, this->position,
                                                                            rotation);
}


void BuildingGrid::set_preview_block(sf::Vector2i position, std::string block_id, int rotation, EngineContext &ctx) {
    this->preview_cells_layer->delete_node(this->preview_cells[position.y][position.x]);

    this->preview_cells[position.y][position.x] = this->block_factory->create_block(block_id,
                                                                                    this->preview_cells_layer, ctx,
                                                                                    {position.x, position.y},
                                                                                    this->sf_cell_size, this->position,
                                                                                    rotation);
}

void BuildingGrid::set_mask_block(sf::Vector2i position, std::string block_id, int rotation, EngineContext &ctx) {
    this->mask_cells_layer->delete_node(this->mask_cells[position.y][position.x]);

    this->mask_cells[position.y][position.x] = this->block_factory->create_block(block_id,
                                                                                 this->mask_cells_layer, ctx,
                                                                                 {position.x, position.y},
                                                                                 this->sf_cell_size, this->position,
                                                                                 rotation);
}