//
// Created by EgorRychkov on 03.05.2025.
//

#include "Blueprint.h"

Blueprint::Blueprint(sf::Vector2i grid_size) {
    this->grid_size = grid_size;
}

std::shared_ptr<BlueprintComponent> Blueprint::add_component() {
    this->components.push_back(BlueprintComponent::create(this->grid_size));
    return this->components.back();
}