//
// Created by EgorRychkov on 28.07.2025.
//

#ifndef LOGISTICHELL_API_H
#define LOGISTICHELL_API_H


#include <memory>
#include "UnitsApi.h"

class Api {
private:
    std::weak_ptr<GameWorld> world;
public:
    Api(const std::shared_ptr<GameWorld> &world);

    std::shared_ptr<UnitsApi> units;
};


#endif //LOGISTICHELL_API_H
