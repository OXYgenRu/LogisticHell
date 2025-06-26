//
// Created by EgorRychkov on 04.05.2025.
//

#include "BlueprintComponent.h"

std::shared_ptr<BlueprintComponent> BlueprintComponent::create(sf::Vector2i grid_size) {
    return std::make_shared<BlueprintComponent>(grid_size);
}

void BlueprintComponent::set_block(sf::Vector2i position, BlueprintBlock new_block) {
    this->grid[position.y][position.x] = new_block;
}


sf::Vector2i BlueprintComponent::get_grid_size() {
    if (grid.empty()) {
        return {int(0), int(0)};
    }
    return {int(grid[0].size()), int(grid.size())};
}

BlueprintBlock &BlueprintComponent::get_block(sf::Vector2i position) {
    return this->grid[position.y][position.x];
}

void BlueprintComponent::delete_block(sf::Vector2i position) {
    this->grid[position.y][position.x].type = BlockType::Empty;
}

void BlueprintComponent::set_body_type(ComponentBodyType new_type) {
    this->body_type = new_type;
}

const ComponentBodyType &BlueprintComponent::get_body_type() {
    return body_type;
}