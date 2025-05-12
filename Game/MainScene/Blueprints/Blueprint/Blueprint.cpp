//
// Created by EgorRychkov on 03.05.2025.
//

#include "Blueprint.h"

sf::Vector2i rotate_grid(sf::Vector2i grid_size, int rotation) {
    switch (rotation % 2) {
        case 0:
            return {grid_size.x, grid_size.y};
        case 1:
            return {grid_size.y, grid_size.x};
    }
    return grid_size;
}


Blueprint::Blueprint(sf::Vector2i grid_size, bool is_unit, int rotation) {
    this->grid_size = rotate_grid(grid_size, rotation);
    this->as_unit = is_unit;
}

std::shared_ptr<BlueprintComponent> Blueprint::add_component() {
    this->components.push_back(BlueprintComponent::create(this->grid_size));
    return this->components.back();
}

std::shared_ptr<BlueprintComponent> Blueprint::get_component(sf::Vector2i position) {
    for (auto &component: this->components) {
        if (component->get_block(position).block_id != "empty_block::empty_block") {
            return component;
        }
    }
    return nullptr;
}

bool Blueprint::is_cell_exist(sf::Vector2i position) const {
    if (position.x < 0 or position.x >= this->grid_size.x) {
        return false;
    }
    if (position.y < 0 or position.y >= this->grid_size.y) {
        return false;
    }
    return true;
}