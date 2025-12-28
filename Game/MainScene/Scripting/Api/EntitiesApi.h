//
// Created by EgorRychkov on 28.12.2025.
//

#ifndef LOGISTICHELL_ENTITIESAPI_H
#define LOGISTICHELL_ENTITIESAPI_H

#include "../../Player/InputListenersSystem.h"


class EntitiesApi {
private:
    std::weak_ptr<GameWorld> world;
public:
    explicit EntitiesApi(const std::shared_ptr<GameWorld> &world);
};


#endif //LOGISTICHELL_ENTITIESAPI_H
