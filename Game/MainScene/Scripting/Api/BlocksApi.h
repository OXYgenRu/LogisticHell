//
// Created by EgorRychkov on 08.08.2025.
//

#ifndef LOGISTICHELL_BLOCKSAPI_H
#define LOGISTICHELL_BLOCKSAPI_H


#include <memory>
#include "SFML/Graphics.hpp"


class GameWorld;

class BlocksApi {
private:
    std::weak_ptr<GameWorld> world;
public:
    explicit BlocksApi(const std::shared_ptr<GameWorld> &world);

    sf::Vector2f get_world_point(const unsigned int &block_id, const sf::Vector2f &relative_position);
//    sf::Vector2f get_world_point(const unsigned int &unit_id, const sf::Vector2i &block_position,
//                                 const sf::Vector2f &relative_position);

};


#endif //LOGISTICHELL_BLOCKSAPI_H
