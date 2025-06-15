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


Blueprint::Blueprint(sf::Vector2i grid_size, int rotation) {
    this->grid_size = rotate_grid(grid_size, rotation);
}

std::shared_ptr<BlueprintComponent> Blueprint::add_component() {
    this->components.push_back(BlueprintComponent::create(this->grid_size));
    return this->components.back();
}

bool Blueprint::is_block_empty(sf::Vector2i position) {
    if (get_component(position) != nullptr) {
        return false;
    }
    return true;
}

std::shared_ptr<BlueprintComponent> Blueprint::get_component(sf::Vector2i position) const {
    for (auto &component: this->components) {
        if (component->get_block(position).type != BlockType::Empty) {
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

void
Blueprint::set_unit_properties(const sf::Vector2i &position, const std::shared_ptr<UnitProperties> &new_properties) {
    this->units_properties[position] = new_properties;
}

std::shared_ptr<UnitProperties> Blueprint::get_unit_properties(const sf::Vector2i &position) const {
    const auto &found = this->units_properties.find(position);
    if (found == this->units_properties.end()) {
        return nullptr;
    }
    return found->second;
}

std::vector<std::shared_ptr<UnitProperties>> &Blueprint::get_units_properties() {
    return this->units;
}

void Blueprint::add_unit_properties(const std::shared_ptr<UnitProperties> &new_properties) {
    this->units.push_back(new_properties);
}