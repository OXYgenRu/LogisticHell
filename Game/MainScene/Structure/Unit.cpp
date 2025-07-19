//
// Created by EgorRychkov on 16.06.2025.
//

#include "Unit.h"


std::shared_ptr<Unit>
Unit::create(const std::shared_ptr<MainScene> &scene, const sf::Vector2i &position, int rotation) {
    auto node = std::make_shared<Unit>();
    node->api = UnitApi(node);
    node->scene = scene;
    node->position = position;
    node->rotation = rotation;
    return node;
}

void Unit::add_block(const std::shared_ptr<ComponentBlock> &new_block) {
    this->blocks[new_block->get_in_component_position()] = new_block;
}

void Unit::set_unit_behavior(const std::shared_ptr<UnitBehavior> &behavior) {
    this->unit_behavior = behavior;
}

const std::shared_ptr<UnitBehavior> &Unit::get_behavior() {
    return this->unit_behavior;
}

void Unit::set_render_feature(const std::string &feature_name, const std::shared_ptr<UnitRenderQuad> &new_feature) {
    this->render_features[feature_name] = new_feature;
}

std::shared_ptr<ComponentBlock> Unit::get_block(const sf::Vector2i &position) {
    auto it = (this->blocks).find(position);
    if (it == this->blocks.end()) {
        return nullptr;
    }
    return it->second;
}


void Unit::set_joint(const std::string &joint_name, const std::shared_ptr<RevoluteJoint> &new_joint) {
    this->joints[joint_name] = new_joint;
}

Unit::~Unit() {
    std::cout << "dest_unit" << '\n';
}


int Unit::get_rotation() const {
    return rotation;
}

const sf::Vector2i &Unit::get_position() {
    return position;
}