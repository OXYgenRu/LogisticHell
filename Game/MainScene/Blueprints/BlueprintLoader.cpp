//
// Created by EgorRychkov on 10.05.2025.
//

#include "BlueprintLoader.h"
#include "iostream"

#include <functional>


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

void BlueprintLoader::register_blueprint(const std::string &blueprint_id, Blueprint template_blueprint) {
    sf::Vector2i grid_size = template_blueprint.grid_size;
    bool as_unit = template_blueprint.as_unit;
    std::vector<std::shared_ptr<BlueprintComponent>> components = template_blueprint.components;
    if (template_blueprint.as_unit) {
        this->units.push_back(blueprint_id);
        std::shared_ptr<UnitProperties> template_unit_properties = std::make_shared<UnitProperties>();
        template_blueprint.add_unit_properties(template_unit_properties);
        for (auto &to: template_blueprint.components) {
            for (int i = 0; i < template_blueprint.grid_size.y; i++) {
                for (int j = 0; j < template_blueprint.grid_size.x; j++) {
                    BlueprintBlock &block = to->get_block({j, i});
                    if (block.block_id != "void_block::void_block" or
                        block.background_block_id != "void_block::void_block") {
                        template_unit_properties->add_unit_block({j, i});
                        template_blueprint.set_unit_properties({j, i}, template_unit_properties);
                    }
                }
            }
        }
    } else {
        this->blueprints.push_back(blueprint_id);
    }
    std::vector<std::shared_ptr<UnitProperties>> template_units = template_blueprint.get_units_properties();
    this->loaders[blueprint_id] = [grid_size, as_unit, components, template_units](int rotation) {
        auto blueprint = std::make_shared<Blueprint>(grid_size, as_unit, rotation);
        for (auto &to: components) {
            std::shared_ptr<BlueprintComponent> component = blueprint->add_component();
            for (int i = 0; i < grid_size.y; i++) {
                for (int j = 0; j < grid_size.x; j++) {
                    sf::Vector2i new_position = get_block_position({j, i}, blueprint->grid_size, rotation);
                    BlueprintBlock block = to->get_block({j, i});
                    block.rotation = (block.rotation + rotation) % 4;
                    component->get_block(new_position) = block;
                }
            }
        }
        for (auto &to: template_units) {
            std::shared_ptr<UnitProperties> new_properties = std::make_shared<UnitProperties>();
            new_properties->get_revolute_joints() = to->get_revolute_joints();
            blueprint->add_unit_properties(new_properties);
            for (sf::Vector2i &block_position: to->get_unit_blocks()) {
                sf::Vector2i new_position = get_block_position(block_position, blueprint->grid_size, rotation);
                new_properties->add_unit_block(new_position);
                blueprint->set_unit_properties(new_position, new_properties);
            }
        }
        return blueprint;
    };
}

std::shared_ptr<Blueprint> BlueprintLoader::create_blueprint(const std::string &blueprint_id, int rotation) {
    auto it = (this->loaders).find(blueprint_id);
    if (it == this->loaders.end()) {
        throw std::runtime_error("Unknown blueprint ID");
    }
    return it->second(rotation);
}

std::vector<std::string> &BlueprintLoader::get_all_blueprints() {
    return this->blueprints;
}

std::vector<std::string> &BlueprintLoader::get_all_units() {
    return this->units;
}