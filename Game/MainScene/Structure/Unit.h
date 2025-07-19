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
#include "UnitApi.h"

class MainScene;


class Unit {
public:
    static std::shared_ptr<Unit>
    create(const std::shared_ptr<MainScene> &scene, const sf::Vector2i &position, int rotation);

    Unit() = default;

    ~Unit();

    void add_block(const std::shared_ptr<ComponentBlock> &new_block);

    std::shared_ptr<ComponentBlock> get_block(const sf::Vector2i &position);

    void set_unit_behavior(const std::shared_ptr<UnitBehavior> &behavior);

    const std::shared_ptr<UnitBehavior> &get_behavior();

    void set_render_feature(const std::string &feature_name, const std::shared_ptr<UnitRenderQuad> &new_feature);

    void set_joint(const std::string &joint_name, const std::shared_ptr<RevoluteJoint> &new_joint);

    int get_rotation() const;

    const sf::Vector2i &get_position();

    UnitApi api;
    std::weak_ptr<MainScene> scene;
private:
    int rotation{};
    sf::Vector2i position;
    std::shared_ptr<UnitBehavior> unit_behavior;
    std::unordered_map<sf::Vector2i, std::shared_ptr<ComponentBlock>> blocks;
    std::unordered_map<std::string, std::shared_ptr<UnitRenderQuad>> render_features;
    std::unordered_map<std::string, std::shared_ptr<RevoluteJoint>> joints;
};


#endif //LOGISTICHELL_UNIT_H
