//
// Created by EgorRychkov on 28.07.2025.
//

#ifndef LOGISTICHELL_API_H
#define LOGISTICHELL_API_H


#include <memory>
#include "UnitsApi.h"
#include "BlocksApi.h"
#include "MouseApi.h"
#include "VectorApi.h"
#include "ListenersApi.h"
#include "PlayersApi.h"
#include "ValuesStorageApi.h"

class Api {
private:
    std::weak_ptr<GameWorld> world;
public:
    Api(const std::shared_ptr<GameWorld> &world, EngineContext &ctx);

    std::shared_ptr<UnitsApi> units;
    std::shared_ptr<BlocksApi> blocks;
    std::shared_ptr<MouseApi> mouse;
    std::shared_ptr<VectorApi> vector;
    std::shared_ptr<ListenersApi> listeners;
    std::shared_ptr<PlayersApi> player;
    std::shared_ptr<ValuesStorageApi> values_storage;
};


#endif //LOGISTICHELL_API_H
