//
// Created by EgorRychkov on 28.07.2025.
//

#include "Api.h"

Api::Api(const std::shared_ptr<GameWorld> &world) {
    this->world = world;
    this->units = std::make_shared<UnitsApi>(world);
}