//
// Created by EgorRychkov on 10.05.2025.
//

#include "BlueprintLoader.h"
#include "iostream"
#include <functional>
#include "../World/GameWorld.h"


sf::Vector2i get_block_position(const sf::Vector2i &position, const sf::Vector2i &grid_size, int rotation) {
    switch (rotation % 4) {
        case 0:
            return position;
        case 1:
            return {position.y, grid_size.y - position.x - 1};
        case 2:
            return {grid_size.x - position.x - 1, grid_size.y - position.y - 1};
        case 3:
            return {grid_size.x - position.y - 1, position.x};
    }
    return position;
}

sf::Vector2f get_relative_position(const sf::Vector2f &position, const sf::Vector2i &grid_size, int rotation) {
    switch (rotation % 4) {
        case 0:
            return position;
        case 1:
            return {position.y, float(grid_size.y) - position.x - 1};
        case 2:
            return {float(grid_size.x) - position.x - 1, float(grid_size.y) - position.y - 1};
        case 3:
            return {float(grid_size.x) - position.y - 1, position.x};
    }
    return position;
}

BlueprintLoader::BlueprintLoader(const std::shared_ptr<GameWorld> &world) {
    this->world = world;
}

void BlueprintLoader::register_blueprint(const std::string &blueprint_name, Blueprint template_blueprint) {
    sf::Vector2i grid_size = template_blueprint.grid_size;
    std::vector<std::shared_ptr<BlueprintComponent>> components = template_blueprint.components;
    this->blueprints.push_back(this->world.lock()->get_blueprints_indexer()->get_blueprint_index(blueprint_name));
    std::vector<std::shared_ptr<UnitProperties>> template_units = template_blueprint.get_units_properties();
    this->loaders[this->world.lock()->get_blueprints_indexer()->get_blueprint_index(
            blueprint_name)] = [grid_size, components, template_units](
            int rotation) {
        auto blueprint = std::make_shared<Blueprint>(grid_size, rotation);
        for (auto &to: components) {
            std::shared_ptr<BlueprintComponent> component = blueprint->add_component();
            component->set_body_type(to->get_body_type());
            for (int i = 0; i < grid_size.y; i++) {
                for (int j = 0; j < grid_size.x; j++) {
                    sf::Vector2i new_position = get_block_position({j, i}, blueprint->grid_size, rotation);
                    BlueprintBlock block = to->get_block({j, i});
                    component->get_block(new_position) = block;
                }
            }
        }
        sf::Transform transform;
        transform.rotate(-float(90 * rotation));
        for (auto &to: template_units) {
            std::shared_ptr<UnitProperties> new_properties = std::make_shared<UnitProperties>(
                    get_block_position(
                            to->position,
                            blueprint->grid_size,
                            rotation),
                    (to->rotation +
                     rotation) % 4);
            new_properties->set_unit_index(to->get_unit_index());
            blueprint->add_unit_properties(new_properties);
            for (auto &revolute_joint: to->get_revolute_joints()) {
                new_properties->add_revolute_joint(BlueprintJoints::RevoluteJoint(revolute_joint.joint_name,
                                                                                  get_block_position(
                                                                                          revolute_joint.block_position,
                                                                                          blueprint->grid_size,
                                                                                          rotation),
                                                                                  get_block_position(
                                                                                          revolute_joint.component_block_a,
                                                                                          blueprint->grid_size,
                                                                                          rotation),
                                                                                  get_block_position(
                                                                                          revolute_joint.component_block_b,
                                                                                          blueprint->grid_size,
                                                                                          rotation)));
            }
            for (auto &render_feature: to->get_render_features()) {
                std::vector<sf::Vector2f> vertices = render_feature.vertices;
                for (int i = 0; i < 4; i++) {
                    vertices[i] = transform.transformPoint(vertices[i]);
                }
                new_properties->add_render_feature(
                        UnitRenderFeature(render_feature.feature_name, render_feature.texture_name,
                                          get_block_position(render_feature.anchor_block,
                                                             blueprint->grid_size,
                                                             rotation
                                          ), render_feature.render_priority,
                                          transform.transformPoint(render_feature.position), vertices,
                                          render_feature.angle));
            }
            for (sf::Vector2i &block_position: to->get_unit_blocks()) {
                sf::Vector2i new_position = get_block_position(block_position, blueprint->grid_size, rotation);
                new_properties->add_unit_block(new_position);
                blueprint->set_unit_properties(new_position, new_properties);
            }
        }
        return blueprint;
    };
}

void BlueprintLoader::register_structure(const std::string &structure_name, Blueprint template_blueprint) {
    this->world.lock()->get_blueprints_indexer()->register_new_blueprint_name(structure_name);
    structures.push_back(this->world.lock()->get_blueprints_indexer()->get_blueprint_index(structure_name));
    this->register_blueprint(structure_name, template_blueprint);
}

void BlueprintLoader::register_unit(const std::string &unit_name, Blueprint template_blueprint,
                                    const std::shared_ptr<UnitProperties> &properties,
                                    const std::shared_ptr<UnitBehavior> &behavior) {
    unsigned int unit_index = this->world.lock()->get_blueprints_indexer()->register_new_blueprint_name(unit_name);
    this->units.push_back(unit_index);
    this->world.lock()->get_behavior_storage()->set_unit_behavior(unit_index, behavior);
    properties->get_unit_blocks().clear();
    properties->set_unit_index(unit_index);
    template_blueprint.add_unit_properties(properties);
    for (auto &to: template_blueprint.components) {
        for (int i = 0; i < template_blueprint.grid_size.y; i++) {
            for (int j = 0; j < template_blueprint.grid_size.x; j++) {
                BlueprintBlock &block = to->get_block({j, i});
                if (block.type != BlockType::Empty) {
                    properties->add_unit_block({j, i});
                    template_blueprint.set_unit_properties({j, i}, properties);
                }
            }
        }
    }
    for (UnitRenderFeature &feature: properties->get_render_features()) {
        if (template_blueprint.get_component(feature.anchor_block)->get_block(feature.anchor_block).type !=
            BlockType::BusyAttachable) {
            throw std::runtime_error("Render feature anchor block doesnt exist");
        }
    }
    this->register_blueprint(unit_name, template_blueprint);
}

std::shared_ptr<Blueprint> BlueprintLoader::create_blueprint(const unsigned int &blueprint_index, int rotation) {
    auto it = (this->loaders).find(blueprint_index);
    if (it == this->loaders.end()) {
        throw std::runtime_error("Unknown blueprint ID");
    }
    return it->second(rotation);
}

std::vector<unsigned int> &BlueprintLoader::get_all_blueprints() {
    return this->blueprints;
}

std::vector<unsigned int> &BlueprintLoader::get_all_units() {
    return this->units;
}


