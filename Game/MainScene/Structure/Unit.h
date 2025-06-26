//
// Created by EgorRychkov on 16.06.2025.
//

#ifndef LOGISTICHELL_UNIT_H
#define LOGISTICHELL_UNIT_H

#include "iostream"
#include "unordered_map"
#include "UnitRenderQuad.h"
#include "memory"
#include "ComponentBlock.h"
#include "../Blueprints/UnitProperties/UnitProperties.h"
#include "../Blueprints/Blueprint/Utils.h"
#include "../../../Engine/Nodes/Physics/RevoluteJoint.h"

class Unit {
public:
    Unit() = default;

    ~Unit();

    void add_block(const std::shared_ptr<ComponentBlock> &new_block);

    std::shared_ptr<ComponentBlock> get_block(const sf::Vector2i &position);

    void set_unit_behavior(const std::shared_ptr<UnitBehavior> &behavior);

    void set_render_feature(const std::string &feature_name, const std::shared_ptr<UnitRenderQuad> &new_feature);

    void set_joint(const std::string &joint_name, const std::shared_ptr<RevoluteJoint> &new_joint);

private:
    std::shared_ptr<UnitBehavior> unit_behavior;
    std::unordered_map<sf::Vector2i, std::shared_ptr<ComponentBlock>> blocks;
    std::unordered_map<std::string, std::shared_ptr<UnitRenderQuad>> render_features;
    std::unordered_map<std::string, std::shared_ptr<RevoluteJoint>> joints;
};


#endif //LOGISTICHELL_UNIT_H
