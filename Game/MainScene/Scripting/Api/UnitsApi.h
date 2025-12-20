//
// Created by EgorRychkov on 28.07.2025.
//

#ifndef LOGISTICHELL_UNITSAPI_H
#define LOGISTICHELL_UNITSAPI_H


#include <SFML/System/Vector2.hpp>
#include <memory>
#include "optional"

class GameWorld;

class UnitBehavior;

class UnitsApi {
private:
    std::weak_ptr<GameWorld> world;
public:
    explicit UnitsApi(const std::shared_ptr<GameWorld> &world);

    void apply_local_force(const unsigned int &unit_id, const sf::Vector2i &block_position,
                           const sf::Vector2f &relative_position,
                           const sf::Vector2f &force);

    void apply_global_force(const unsigned int &unit_id, const sf::Vector2i &block_position,
                            const sf::Vector2f &relative_position,
                            const sf::Vector2f &force);

    void set_unit_behavior(const unsigned int &unit_index, const std::shared_ptr<UnitBehavior> &behavior);

    const std::string & get_unit_name(unsigned int unit_index);

    unsigned int get_unit_index(const std::string &unit_name);

    std::optional<unsigned int> get_block(const unsigned int &unit_id, const sf::Vector2i &block_position);
//    sf::Vector2f get_world_point(const unsigned int &unit_id, const sf::Vector2i &block_position,
//                                 const sf::Vector2f &relative_position);

};


#endif //LOGISTICHELL_UNITSAPI_H
