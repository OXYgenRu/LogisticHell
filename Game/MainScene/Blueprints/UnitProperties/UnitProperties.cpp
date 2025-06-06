//
// Created by EgorRychkov on 31.05.2025.
//

#include "UnitProperties.h"

UnitProperties::UnitProperties(const sf::Vector2i &position, const std::shared_ptr<UnitProperties> &other) {
    for (BlueprintJoints::RevoluteJoint &joint: other->get_revolute_joints()) {
        this->revolute_joints.emplace_back(joint.block_position_a + position, joint.block_position_b + position);
    }
    this->revolute_joints = other->revolute_joints;
    for (sf::Vector2i &block_position: other->get_unit_blocks()) {
        this->add_unit_block(block_position + position);
    }
}

void UnitProperties::add_revolute_joint(const BlueprintJoints::RevoluteJoint &new_revolute_joint) {
    this->revolute_joints.push_back(new_revolute_joint);
}

std::vector<BlueprintJoints::RevoluteJoint> &UnitProperties::get_revolute_joints() {
    return this->revolute_joints;
}

std::vector<sf::Vector2i> &UnitProperties::get_unit_blocks() {
    return this->unit_blocks;
}

void UnitProperties::add_unit_block(const sf::Vector2i &new_position) {
    this->unit_blocks.push_back(new_position);
}