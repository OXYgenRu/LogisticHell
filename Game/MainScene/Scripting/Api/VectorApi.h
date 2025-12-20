//
// Created by EgorRychkov on 11.08.2025.
//

#ifndef LOGISTICHELL_VECTORAPI_H
#define LOGISTICHELL_VECTORAPI_H

#include <memory>
#include "SFML/Graphics.hpp"

class GameWorld;

class VectorApi {
private:
    std::weak_ptr<GameWorld> world;
public:
    explicit VectorApi(const std::shared_ptr<GameWorld> &world);

    float get_length(const sf::Vector2f &vector);
};


#endif //LOGISTICHELL_VECTORAPI_H
