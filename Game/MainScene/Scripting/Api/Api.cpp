//
// Created by EgorRychkov on 28.07.2025.
//

#include "Api.h"

Api::Api(const std::shared_ptr<GameWorld> &world, EngineContext &ctx) {
    this->world = world;
    this->units = std::make_shared<UnitsApi>(world);
    this->blocks = std::make_shared<BlocksApi>(world);
    this->mouse = std::make_shared<MouseApi>(world, ctx);
    this->vector = std::make_shared<VectorApi>(world);
    this->listeners = std::make_shared<ListenersApi>(world);
    this->player = std::make_shared<PlayersApi>(world);
    this->values_storage = std::make_shared<ValuesStorageApi>(world);
}