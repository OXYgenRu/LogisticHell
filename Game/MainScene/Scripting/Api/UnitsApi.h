//
// Created by EgorRychkov on 28.07.2025.
//

#ifndef LOGISTICHELL_UNITSAPI_H
#define LOGISTICHELL_UNITSAPI_H


#include <SFML/System/Vector2.hpp>
#include <memory>

class GameWorld;

class UnitsApi {
private:
    std::weak_ptr<GameWorld> world;
public:
    UnitsApi(const std::shared_ptr<GameWorld> &world);

    void apply_force(const unsigned int &unit_id, const sf::Vector2i &block_position,
                     const sf::Vector2f &relative_position,
                     const sf::Vector2f &force);
};


#endif //LOGISTICHELL_UNITSAPI_H
