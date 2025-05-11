//
// Created by EgorRychkov on 10.05.2025.
//

#include "BlueprintLoader.h"

void BlueprintLoader::register_blueprint(const std::string &blueprint_id, sf::Vector2i grid_size, bool is_unit,
                                         std::vector<std::shared_ptr<BlueprintComponent>> &components) {
    this->loaders[blueprint_id] = [grid_size, is_unit, components]() {
        auto blueprint = std::make_shared<Blueprint>(grid_size, is_unit);
        for (auto &to: components) {
            std::shared_ptr<BlueprintComponent> component = blueprint->add_component();
            for (int i = 0; i < component->grid.size(); i++) {
                for (int j = 0; j < component->grid[i].size(); j++) {
                    component->grid[i][j] = to->get_block({j, i});
                    if (is_unit) {
                        component->grid[i][j].unit_size = grid_size;
                        component->grid[i][j].unit_offset = {j, i};
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
    this->loaders[blueprint_id] = [grid_size, is_unit, components]() {
        auto blueprint = std::make_shared<Blueprint>(grid_size, is_unit);
        for (auto &to: components) {
            std::shared_ptr<BlueprintComponent> component = blueprint->add_component();
            for (int i = 0; i < component->grid.size(); i++) {
                for (int j = 0; j < component->grid[i].size(); j++) {
                    component->grid[i][j] = to->get_block({j, i});
                    if (is_unit) {
                        component->grid[i][j].unit_size = grid_size;
                        component->grid[i][j].unit_offset = {j, i};
                    }
                }
            }
        }
        return blueprint;
    };
}

std::shared_ptr<Blueprint> BlueprintLoader::create_blueprint(const std::string &blueprint_id) {
    auto it = (this->loaders).find(blueprint_id);
    if (it == this->loaders.end()) {
        throw std::runtime_error("Unknown blueprint ID");
    }
    return it->second();
}