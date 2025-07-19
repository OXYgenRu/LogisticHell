//
// Created by EgorRychkov on 31.05.2025.
//

#include "UnitProperties.h"


UnitProperties::UnitProperties(const std::shared_ptr<UnitBehavior> &behavior, const sf::Vector2i &position,
                               int rotation) {
    this->behavior = behavior;
    this->position = position;
    this->rotation = rotation;
}

UnitProperties::UnitProperties(const sf::Vector2i &position, const std::shared_ptr<UnitProperties> &other,
                               int rotation) {
    this->behavior = other->behavior;
    this->rotation = rotation;
    this->position = position + other->position;
    for (BlueprintJoints::RevoluteJoint &joint: other->get_revolute_joints()) {
        this->revolute_joints.emplace_back(joint.joint_name, joint.block_position + position,
                                           joint.component_block_a + position, joint.component_block_b + position);
    }
    for (sf::Vector2i &block_position: other->get_unit_blocks()) {
        this->add_unit_block(block_position + position);
    }
    for (UnitRenderFeature &feature: other->render_features) {
        this->render_features.emplace_back(feature.feature_name, feature.texture_name, feature.anchor_block + position,
                                           feature.render_priority,
                                           feature.position, feature.vertices, feature.angle);
    }
}

void UnitProperties::add_revolute_joint(const BlueprintJoints::RevoluteJoint &new_revolute_joint) {
    this->revolute_joints.push_back(new_revolute_joint);
}

std::vector<BlueprintJoints::RevoluteJoint> &UnitProperties::get_revolute_joints() {
    return this->revolute_joints;
}

std::shared_ptr<UnitBehavior> &UnitProperties::get_behavior() {
    return this->behavior;
}

std::vector<sf::Vector2i> &UnitProperties::get_unit_blocks() {
    return this->unit_blocks;
}

void UnitProperties::add_unit_block(const sf::Vector2i &new_position) {
    this->unit_blocks.push_back(new_position);
}

void UnitProperties::add_render_feature(const UnitRenderFeature &new_feature) {
    this->render_features.emplace_back(new_feature);
}

std::vector<UnitRenderFeature> &UnitProperties::get_render_features() {
    return this->render_features;
}

