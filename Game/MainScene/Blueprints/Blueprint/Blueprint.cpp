//
// Created by EgorRychkov on 03.05.2025.
//

#include "Blueprint.h"

Blueprint::Blueprint(sf::Vector2i grid_size, bool is_unit) {
    this->grid_size = grid_size;
    this->as_unit = is_unit;
}

Blueprint::Blueprint(sf::Vector2i grid_size, bool is_unit,
                     std::vector<std::shared_ptr<BlueprintComponent>> &components) {
    this->grid_size = grid_size;
    this->as_unit = is_unit;
    this->components = components;
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

bool Blueprint::is_cell_exist(sf::Vector2i position) const{
    if (position.x < 0 or position.x >= this->grid_size.x) {
        return false;
    }
    if (position.y < 0 or position.y >= this->grid_size.y) {
        return false;
    }
    return true;
}