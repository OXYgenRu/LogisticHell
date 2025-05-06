//
// Created by EgorRychkov on 04.05.2025.
//

#include "Builder.h"


std::shared_ptr<Builder> Builder::create(std::shared_ptr<BuildingGrid> building_grid) {
    auto builder = std::make_shared<Builder>(building_grid);
    return builder;
}

Builder::Builder(std::shared_ptr<BuildingGrid> building_grid) {
    this->building_grid = building_grid;
    this->attach_direction = {0, 1};
    this->attach_directions = {{0,  1},
                               {1,  0},
                               {0,  -1},
                               {-1, 0}};
    this->attach_direction_index = 0;
}

void Builder::set_default_blueprint(EngineContext &ctx) {
    this->blueprint = std::make_shared<Blueprint>(this->building_grid->grid_size);
    this->blueprint->add_component()->get_block({0, 0}).block_id = 1;;
    this->building_grid->clear(ctx);
    this->building_grid->set_block({0, 0}, 1, ctx);
}

void Builder::attach_block(sf::Vector2i position, EngineContext &ctx) {
    if (!this->validate_block_attachment(position)) {
        return;
    }
    this->building_grid->set_block(position, 1, ctx);
    this->get_block_attachment_component(position)->set_block(position, BlueprintBlock(1, {0, 0}));
}

bool Builder::validate_block_attachment(sf::Vector2i position) {
    sf::Vector2i block_attachment_base = position + this->attach_direction;
    if (block_attachment_base.x < 0 or block_attachment_base.x >= this->building_grid->grid_size.x) {
        return false;
    }
    if (block_attachment_base.y < 0 or block_attachment_base.y >= this->building_grid->grid_size.y) {
        return false;
    }
    for (auto &component: this->blueprint->components) {
        if (component->get_block(block_attachment_base).block_id != 0) {
            return true;
        }
    }
    return false;
}

std::shared_ptr<BlueprintComponent> Builder::get_block_attachment_component(sf::Vector2i position) {
    sf::Vector2i block_attachment_base = position + this->attach_direction;
    for (auto &component: this->blueprint->components) {
        if (component->get_block(block_attachment_base).block_id != 0) {
            return component;
        }
    }
    return nullptr;
}

void Builder::set_attach_direction(int new_attach_direction_index) {
    this->attach_direction_index = new_attach_direction_index;
    this->attach_direction = this->attach_directions[this->attach_direction_index];
}