//
// Created by EgorRychkov on 11.08.2025.
//

#include "VectorApi.h"
#include "cmath"


VectorApi::VectorApi(const std::shared_ptr<GameWorld> &world) {
    this->world = world;
}

float VectorApi::get_length(const sf::Vector2f &vector) {
    return std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
}