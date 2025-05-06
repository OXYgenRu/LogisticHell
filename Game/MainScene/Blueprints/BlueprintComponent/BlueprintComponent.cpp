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

BlueprintBlock &BlueprintComponent::get_block(sf::Vector2i position) {
    return this->grid[position.y][position.x];
}