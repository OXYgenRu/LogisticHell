//
// Created by EgorRychkov on 31.05.2025.
//

#ifndef LOGISTICHELL_UNITPROPERTIES_H
#define LOGISTICHELL_UNITPROPERTIES_H

#include "SFML/Graphics.hpp"
#include "memory"

namespace BlueprintJoints {
    struct RevoluteJoint {
        sf::Vector2i block_position_a, block_position_b;

        RevoluteJoint(const sf::Vector2i &block_position_a, const sf::Vector2i &block_position_b) {
            this->block_position_a = block_position_a;
            this->block_position_b = block_position_b;
        }
    };
}

class UnitProperties {
public:
    UnitProperties() = default;

    UnitProperties(const sf::Vector2i &position, const std::shared_ptr<UnitProperties> &other);

    void add_revolute_joint(const BlueprintJoints::RevoluteJoint &new_revolute_joint);

    void add_unit_block(const sf::Vector2i &new_position);

    std::vector<sf::Vector2i> &get_unit_blocks();

    std::vector<BlueprintJoints::RevoluteJoint> &get_revolute_joints();

private:
    std::vector<BlueprintJoints::RevoluteJoint> revolute_joints;
    std::vector<sf::Vector2i> unit_blocks;
};


#endif //LOGISTICHELL_UNITPROPERTIES_H
