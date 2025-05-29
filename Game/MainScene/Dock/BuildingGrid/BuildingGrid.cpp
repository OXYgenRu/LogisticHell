//
// Created by EgorRychkov on 03.05.2025.
//

#include <iostream>
#include "BuildingGrid.h"


std::shared_ptr<Cell> Cell::create(const std::shared_ptr<Node> &parent, float sf_cell_size,
                                   const sf::Vector2i &position,
                                   const std::shared_ptr<BlockFactory> &block_factory,
                                   int render_priority) {
    auto node = std::make_shared<Cell>(parent, render_priority);
    Cell::setup(node, sf_cell_size, position, block_factory);
    parent->add_node(node);
    return node;
}


void Cell::setup(const std::shared_ptr<Cell> &node, float sf_cell_size,
                 const sf::Vector2i &position,
                 const std::shared_ptr<BlockFactory> &block_factory) {
    node->sf_cell_size = sf_cell_size;
    node->position = position;
    node->block_factory = block_factory;
}

void Cell::set_default_state(EngineContext &ctx) {
    this->background_block_id = "void_block::void_block";
    this->block_id = "void_block::void_block";
    this->preview_background_block_id = "void_block::void_block";
    this->preview_block_id = "void_block::void_block";
    this->mask_block_id = "empty_block::empty_block";

    this->background_block = block_factory->create_block(background_block_id, shared_from_this(), ctx, position,
                                                         sf_cell_size, 0, 0);
    this->block = block_factory->create_block(block_id, shared_from_this(), ctx, position,
                                              sf_cell_size, 0, 1);
    this->preview_background_block = block_factory->create_block(preview_background_block_id, shared_from_this(), ctx,
                                                                 position,
                                                                 sf_cell_size, 0, 2);
    this->preview_block = block_factory->create_block(preview_block_id, shared_from_this(), ctx, position,
                                                      sf_cell_size, 0, 3);
    this->mask_block = block_factory->create_block(mask_block_id, shared_from_this(), ctx, position,
                                                   sf_cell_size, 0, 4);
}


void Cell::set_background_block(const std::string &new_background_block_id, EngineContext &ctx, int rotation) {
    this->background_block_id = new_background_block_id;
    this->delete_node(this->background_block);
    this->background_block = block_factory->create_block(background_block_id, shared_from_this(), ctx, position,
                                                         sf_cell_size, rotation, 0);
}

void Cell::set_block(const std::string &new_block_id, EngineContext &ctx, int rotation) {
    this->block_id = new_block_id;
    this->delete_node(this->block);
    this->block = block_factory->create_block(block_id, shared_from_this(), ctx, position,
                                              sf_cell_size, rotation, 1);
}

void Cell::set_preview_background_block(const std::string &new_preview_background_block_id, EngineContext &ctx,
                                        int rotation) {
    this->preview_background_block_id = new_preview_background_block_id;
    this->delete_node(this->preview_background_block);
    this->preview_background_block = block_factory->create_block(preview_background_block_id, shared_from_this(), ctx,
                                                                 position,
                                                                 sf_cell_size, rotation, 2);
}

void Cell::set_preview_block(const std::string &new_preview_block_id, EngineContext &ctx, int rotation) {
    this->preview_block_id = new_preview_block_id;
    this->delete_node(this->preview_block);
    this->preview_block = block_factory->create_block(preview_block_id, shared_from_this(), ctx, position,
                                                      sf_cell_size, rotation, 3);
}

void Cell::set_mask_block(const std::string &new_mask_block_id, EngineContext &ctx, int rotation) {
    this->mask_block_id = new_mask_block_id;
    this->delete_node(this->mask_block);
    this->mask_block = block_factory->create_block(mask_block_id, shared_from_this(), ctx, position,
                                                   sf_cell_size, rotation, 4);
}

void Cell::set_cell_position(const sf::Vector2i &new_cell_position) {
    this->position = new_cell_position;
}

std::shared_ptr<BuildingGrid>
BuildingGrid::create(const std::shared_ptr<Node> &parent, const std::shared_ptr<Dock> &dock,
                     float sf_cell_size, const sf::Vector2i &grid_size,
                     const std::shared_ptr<BlockFactory> &block_factory,
                     int render_priority) {
    auto node = std::make_shared<BuildingGrid>(parent, render_priority);
    BuildingGrid::setup(node, dock, sf_cell_size, grid_size, block_factory);
    parent->add_node(node);
    return node;
}

void BuildingGrid::set_default_state(EngineContext &ctx) {
    for (int i = 0; i < this->grid_size.y; i++) {
        for (int j = 0; j < this->grid_size.x; j++) {
            this->cells[i][j] = Cell::create(shared_from_this(), sf_cell_size, {j, grid_size.y - i - 1},
                                             this->block_factory);
            this->cells[i][j]->set_default_state(ctx);

        }
    }
}


void BuildingGrid::setup(const std::shared_ptr<BuildingGrid> &node, const std::shared_ptr<Dock> &dock,
                         float sf_cell_size, const sf::Vector2i &grid_size,
                         const std::shared_ptr<BlockFactory> &block_factory) {

    node->grid_collider = UI::Collider::create(node);
    node->grid_collider->set_vertices(
            {sf::Vector2f(0, 0), sf::Vector2f(grid_size.x * sf_cell_size, 0),
             sf::Vector2f(grid_size.x * sf_cell_size, grid_size.y * sf_cell_size),
             sf::Vector2f(0, grid_size.y * sf_cell_size)});

    node->grid_collider->set_position(sf::Vector2f(-sf_cell_size / 2, -sf_cell_size / 2));


    node->cells.resize(grid_size.y, std::vector<std::shared_ptr<Cell>>(grid_size.x));
    node->dock = dock;
    node->sf_cell_size = sf_cell_size;
    node->grid_size = grid_size;
    node->block_factory = block_factory;

}

void BuildingGrid::clear_background(EngineContext &ctx) {
    for (int i = 0; i < this->grid_size.y; i++) {
        for (int j = 0; j < this->grid_size.x; j++) {
            this->cells[i][j]->set_background_block("void_block::void_block", ctx, 0);
        }
    }
}


void BuildingGrid::clear(EngineContext &ctx) {
    for (int i = 0; i < this->grid_size.y; i++) {
        for (int j = 0; j < this->grid_size.x; j++) {
            this->cells[i][j]->set_block("void_block::void_block", ctx, 0);
        }
    }
}


void BuildingGrid::clear_preview(EngineContext &ctx) {
    for (int i = 0; i < this->grid_size.y; i++) {
        for (int j = 0; j < this->grid_size.x; j++) {
            this->cells[i][j]->set_preview_block("void_block::void_block", ctx, 0);
        }
    }
}

void BuildingGrid::clear_background_preview(EngineContext &ctx) {
    for (int i = 0; i < this->grid_size.y; i++) {
        for (int j = 0; j < this->grid_size.x; j++) {
            this->cells[i][j]->set_preview_background_block("void_block::void_block", ctx, 0);
        }
    }
}

void BuildingGrid::clear_mask(EngineContext &ctx) {
    for (int i = 0; i < this->grid_size.y; i++) {
        for (int j = 0; j < this->grid_size.x; j++) {
            this->cells[i][j]->set_mask_block("void_block::void_block", ctx, 0);
        }
    }
}

void BuildingGrid::set_background_block(const sf::Vector2i &position, const std::string &block_id, int rotation,
                                        EngineContext &ctx) {
    this->cells[position.y][position.x]->set_background_block(block_id, ctx, rotation);
}


void
BuildingGrid::set_block(const sf::Vector2i &position, const std::string &block_id, int rotation, EngineContext &ctx) {
    this->cells[position.y][position.x]->set_block(block_id, ctx, rotation);
}

void BuildingGrid::set_background_preview_block(const sf::Vector2i &position, const std::string &block_id, int rotation,
                                                EngineContext &ctx) {
    this->cells[position.y][position.x]->set_preview_background_block(block_id, ctx, rotation);
}

void BuildingGrid::set_preview_block(sf::Vector2i const &position, const std::string &block_id, int rotation,
                                     EngineContext &ctx) {
    this->cells[position.y][position.x]->set_preview_block(block_id, ctx, rotation);
}

void BuildingGrid::set_mask_block(const sf::Vector2i &position, const std::string &block_id, int rotation,
                                  EngineContext &ctx) {
    this->cells[position.y][position.x]->set_mask_block(block_id, ctx, rotation);
}