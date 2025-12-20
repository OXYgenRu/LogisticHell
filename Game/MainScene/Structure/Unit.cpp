//
// Created by EgorRychkov on 16.06.2025.
//

#include "Unit.h"


std::shared_ptr<Unit>
Unit::create(const std::shared_ptr<GameWorld> &world, const sf::Vector2i &position, int rotation,
             const unsigned int &unit_index, const unsigned int &unit_id) {
    auto node = std::make_shared<Unit>();
    node->unit_index = unit_index;
    node->unit_id = unit_id;
    node->world = world;
    node->position = position;
    node->rotation = rotation;
    return node;
}

void Unit::add_block(const std::shared_ptr<ComponentBlock> &new_block) {
    this->blocks[new_block->get_in_component_position()] = new_block;
}


void Unit::set_render_feature(const std::string &feature_name, const std::shared_ptr<UnitRenderQuad> &new_feature) {
    this->render_features[feature_name] = new_feature;
}

void Unit::delete_render_feature(const std::string &feature_name) {
    auto it = (this->render_features).find(feature_name);
    if (it == this->render_features.end()) {
        return;
    }
    this->render_features.erase(it);
}

std::shared_ptr<ComponentBlock> Unit::get_block(const sf::Vector2i &position) {
    auto it = (this->blocks).find(position);
    if (it == this->blocks.end()) {
        return nullptr;
    }
    return it->second;
}


void Unit::delete_block(const sf::Vector2i &position) {
    auto it = (this->blocks).find(position);
    if (it == this->blocks.end()) {
        return;
    }
    (this->blocks).erase(it);
}

void Unit::set_joint(const std::string &joint_name, const std::shared_ptr<RevoluteJoint> &new_joint) {
    this->joints[joint_name] = new_joint;
}

std::unordered_map<sf::Vector2i, std::shared_ptr<ComponentBlock>> &Unit::get_blocks() {
    return this->blocks;
}

Unit::~Unit() {
    std::cout << "Unit destroyed" << '\n';
}


int Unit::get_rotation() const {
    return rotation;
}

const sf::Vector2i &Unit::get_position() {
    return position;
}

const unsigned int &Unit::get_unit_index() {
    return this->unit_index;
}

const unsigned int &Unit::get_unit_id() {
    return this->unit_id;
}