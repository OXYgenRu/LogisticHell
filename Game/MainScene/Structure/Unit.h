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

class GameWorld;

class Unit {
public:
    static std::shared_ptr<Unit>
    create(const std::shared_ptr<GameWorld> &world, const sf::Vector2i &position, int rotation,
           const unsigned int &unit_index, const unsigned int &unit_id);

    Unit() = default;

    ~Unit();

    void add_block(const std::shared_ptr<ComponentBlock> &new_block);

    std::shared_ptr<ComponentBlock> get_block(const sf::Vector2i &position);

    void delete_block(const sf::Vector2i &position);

    void set_render_feature(const std::string &feature_name, const std::shared_ptr<UnitRenderQuad> &new_feature);

    void delete_render_feature(const std::string &feature_name);

    void set_joint(const std::string &joint_name, const std::shared_ptr<RevoluteJoint> &new_joint);

    std::unordered_map<sf::Vector2i, std::shared_ptr<ComponentBlock>> &get_blocks();

    int get_rotation() const;

    const sf::Vector2i &get_position();

    const unsigned int &get_unit_index();

    const unsigned int &get_unit_id();

    std::weak_ptr<GameWorld> world;
private:
    unsigned int unit_index;
    unsigned int unit_id;

    int rotation{};
    sf::Vector2i position;
    std::unordered_map<sf::Vector2i, std::shared_ptr<ComponentBlock>> blocks;
    std::unordered_map<std::string, std::shared_ptr<UnitRenderQuad>> render_features;
    std::unordered_map<std::string, std::shared_ptr<RevoluteJoint>> joints;
};


#endif //LOGISTICHELL_UNIT_H
