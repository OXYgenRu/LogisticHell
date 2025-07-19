//
// Created by EgorRychkov on 31.05.2025.
//

#ifndef LOGISTICHELL_UNITPROPERTIES_H
#define LOGISTICHELL_UNITPROPERTIES_H

#include "SFML/Graphics.hpp"
#include "memory"
#include "UnitRenderFeature.h"

class Unit;

class UnitBehavior;

namespace BlueprintJoints {
    struct RevoluteJoint {
        sf::Vector2i block_position;
        sf::Vector2i component_block_a, component_block_b;
        std::string joint_name;

        RevoluteJoint(const std::string &joint_name, const sf::Vector2i &block_position,
                      sf::Vector2i component_block_a, sf::Vector2i component_block_b) {
            this->joint_name = joint_name;
            this->block_position = block_position;
            this->component_block_a = component_block_a;
            this->component_block_b = component_block_b;
        }
    };

    struct WeldJoint {
        
    };
}

class UnitProperties {
public:
    UnitProperties(const std::shared_ptr<UnitBehavior> &behavior, const sf::Vector2i &position, int rotation);

    UnitProperties(const sf::Vector2i &position, const std::shared_ptr<UnitProperties> &other, int rotation);

    void add_revolute_joint(const BlueprintJoints::RevoluteJoint &new_revolute_joint);

    void add_unit_block(const sf::Vector2i &new_position);

    void add_render_feature(const UnitRenderFeature &new_feature);

    std::shared_ptr<UnitBehavior> &get_behavior();

    std::vector<sf::Vector2i> &get_unit_blocks();

    std::vector<BlueprintJoints::RevoluteJoint> &get_revolute_joints();

    std::vector<UnitRenderFeature> &get_render_features();

    int rotation;
    sf::Vector2i position;
private:
    std::shared_ptr<UnitBehavior> behavior;
    std::vector<BlueprintJoints::RevoluteJoint> revolute_joints;
    std::vector<sf::Vector2i> unit_blocks;
    std::vector<UnitRenderFeature> render_features;
};


#endif //LOGISTICHELL_UNITPROPERTIES_H
