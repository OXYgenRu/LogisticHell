//
// Created by EgorRychkov on 09.08.2025.
//

#ifndef LOGISTICHELL_MOUSEAPI_H
#define LOGISTICHELL_MOUSEAPI_H

#include <memory>
#include "SFML/Graphics.hpp"
#include "../../../../Engine/EngineContext.h"


class GameWorld;

class MouseApi {
private:
    std::weak_ptr<GameWorld> world;
    EngineContext &ctx;
public:
    MouseApi(const std::shared_ptr<GameWorld> &world, EngineContext &ctx);

    sf::Vector2f get_world_mouse_position();
};


#endif //LOGISTICHELL_MOUSEAPI_H
