//
// Created by EgorRychkov on 10.05.2025.
//

#include "BlueprintLoader.h"
#include "iostream"

sf::Vector2i get_block_position(sf::Vector2i position, sf::Vector2i &grid_size, int rotation) {
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

void BlueprintLoader::register_blueprint(const std::string &blueprint_id, sf::Vector2i grid_size, bool is_unit,
                                         std::vector<std::shared_ptr<BlueprintComponent>> &components) {
    this->blueprints.push_back(blueprint_id);
    this->loaders[blueprint_id] = [grid_size, is_unit, components](int rotation) {
        auto blueprint = std::make_shared<Blueprint>(grid_size, is_unit, rotation);
        for (auto &to: components) {
            std::shared_ptr<BlueprintComponent> component = blueprint->add_component();
            for (int i = 0; i < grid_size.y; i++) {
                for (int j = 0; j < grid_size.x; j++) {
                    sf::Vector2i new_position = get_block_position({j, i}, blueprint->grid_size, rotation);
                    component->get_block(new_position) = to->get_block({j, i});
                    component->get_block(new_position).rotation = rotation;
                    if (is_unit) {
                        component->get_block(new_position).unit_size = blueprint->grid_size;
                        component->get_block(new_position).unit_offset = new_position;
                    }
                }
            }
        }
        return blueprint;
    };
}


void BlueprintLoader::register_blueprint(const std::string &blueprint_id, Blueprint &template_blueprint) {
    sf::Vector2i grid_size = template_blueprint.grid_size;
    bool is_unit = template_blueprint.as_unit;
    std::vector<std::shared_ptr<BlueprintComponent>> components = template_blueprint.components;
    this->blueprints.push_back(blueprint_id);
    this->loaders[blueprint_id] = [grid_size, is_unit, components](int rotation) {
        auto blueprint = std::make_shared<Blueprint>(grid_size, is_unit, rotation);
        for (auto &to: components) {
            std::shared_ptr<BlueprintComponent> component = blueprint->add_component();
            for (int i = 0; i < grid_size.y; i++) {
                for (int j = 0; j < grid_size.x; j++) {
                    sf::Vector2i new_position = get_block_position({j, i}, blueprint->grid_size, rotation);
                    component->get_block(new_position) = to->get_block({j, i});
                    component->get_block(new_position).rotation =
                            (component->get_block(new_position).rotation + rotation) % 4;
                    if (is_unit) {
                        component->get_block(new_position).unit_size = blueprint->grid_size;
                        component->get_block(new_position).unit_offset = new_position;
                    }
                }
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