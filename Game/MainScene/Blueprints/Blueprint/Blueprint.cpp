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

bool Blueprint::is_block_empty(sf::Vector2i position) {
    if (get_component(position, true) != nullptr) {
        return false;
    }
    if (get_component(position, false) != nullptr) {
        return false;
    }
    return true;
}

std::shared_ptr<BlueprintComponent> Blueprint::get_component(sf::Vector2i position, bool find_background) {
    for (auto &component: this->components) {
        if (find_background) {
            if (component->get_block(position).background_block_id != "void_block::void_block") {
                return component;
            }
        } else {
            if (component->get_block(position).block_id != "void_block::void_block") {
                return component;
            }
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