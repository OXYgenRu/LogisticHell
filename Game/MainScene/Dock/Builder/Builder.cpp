//
// Created by EgorRychkov on 04.05.2025.
//

#include <iostream>
#include "Builder.h"


std::shared_ptr<Builder>
Builder::create(std::shared_ptr<BuildingGrid> building_grid, std::shared_ptr<BlueprintLoader> blueprint_loader) {
    auto builder = std::make_shared<Builder>(building_grid, blueprint_loader);
    return builder;
}

Builder::Builder(std::shared_ptr<BuildingGrid> building_grid, std::shared_ptr<BlueprintLoader> blueprint_loader) {
    this->building_grid = building_grid;
    this->blueprint_loader = blueprint_loader;
    this->attach_direction = {0, 1};
    this->attach_directions = {{0,  1},
                               {1,  0},
                               {0,  -1},
                               {-1, 0}};
    this->attach_direction_index = 0;
    this->unit_id = "big_construction";
    this->preview_position = {0, 0};
}

void Builder::set_default_blueprint(EngineContext &ctx) {
    this->blueprint = std::make_shared<Blueprint>(this->building_grid->grid_size, false, 0);
    this->blueprint->add_component()->get_block({0, 0}).block_id = "construction_block::construction_block";
    this->building_grid->clear(ctx);
    this->building_grid->set_block({0, 0}, "construction_block::construction_block", 0, ctx);
}

void Builder::attach_unit(sf::Vector2i position, EngineContext &ctx) {
    std::shared_ptr<Blueprint> unit = this->blueprint_loader.lock()->create_blueprint(this->unit_id,
                                                                                      this->preview_rotation);
    sf::Vector2i unit_position = {position.x - unit->grid_size.x / 2, position.y - unit->grid_size.y / 2};
    if (!this->validate_unit_attachment(unit_position)) {
        return;
    }

    std::shared_ptr<BlueprintComponent> unit_attachment_base = this->blueprint_attachment_components[this->selected_blueprint_component_index];
    std::shared_ptr<BlueprintComponent> unit_connecting_component = unit->components[this->selected_preview_component_index];
    for (int y = 0; y < unit->grid_size.y; y++) {
        for (int x = 0; x < unit->grid_size.x; x++) {
            BlueprintBlock block = unit_connecting_component->get_block({x, y});
            if (block.block_id != "empty_block::empty_block") {
                unit_attachment_base->set_block({unit_position.x + x, unit_position.y + y}, block);
                this->building_grid->set_block({unit_position.x + x, unit_position.y + y}, block.block_id,
                                               this->preview_rotation, ctx);
            }
        }
    }
    for (auto &component: unit->components) {
        if (component == unit_connecting_component) {
            continue;
        }
        std::shared_ptr<BlueprintComponent> new_component = this->blueprint->add_component();
        for (int y = 0; y < unit->grid_size.y; y++) {
            for (int x = 0; x < unit->grid_size.x; x++) {
                BlueprintBlock block = component->get_block({x, y});
                if (block.block_id != "empty_block::empty_block") {
                    new_component->set_block({unit_position.x + x, unit_position.y + y}, block);
                    this->building_grid->set_block({unit_position.x + x, unit_position.y + y}, block.block_id,
                                                   this->preview_rotation, ctx);
                }
            }
        }
    }
    this->find_blueprint_attachment_components();
}

bool Builder::validate_unit_attachment(sf::Vector2i position) {
    std::shared_ptr<Blueprint> unit = this->blueprint_loader.lock()->create_blueprint(this->unit_id,
                                                                                      this->preview_rotation);
    if (this->blueprint_attachment_components.empty()) {
        return false;
    }
    for (int y = 0; y < unit->grid_size.y; y++) {
        for (int x = 0; x < unit->grid_size.x; x++) {
            if (unit->get_component({x, y}) == nullptr) {
                continue;
            }
            if (!this->blueprint->is_cell_exist({position.x + x, position.y + y})) {
                return false;
            }
            if (this->blueprint->get_component({position.x + x, position.y + y}) != nullptr and
                unit->get_component({x, y}) != nullptr) {
                return false;
            }
        }
    }
    return true;
}

void Builder::set_attach_direction(int new_attach_direction_index) {
    this->attach_direction_index = new_attach_direction_index;
    this->attach_direction = this->attach_directions[this->attach_direction_index];
}


void Builder::update_preview(EngineContext &ctx) {
    std::shared_ptr<Blueprint> unit = this->blueprint_loader.lock()->create_blueprint(this->unit_id,
                                                                                      this->preview_rotation);
    sf::Vector2i unit_position = {this->preview_position.x - unit->grid_size.x / 2,
                                  this->preview_position.y - unit->grid_size.y / 2};
    std::shared_ptr<BlueprintComponent> &selected_component = unit->components[this->selected_preview_component_index];

    std::vector<sf::Vector2i> bias = {{0,  1},
                                      {1,  0},
                                      {0,  -1},
                                      {-1, 0}};


    for (int y = 0; y < blueprint->grid_size.y; y++) {
        for (int x = 0; x < blueprint->grid_size.x; x++) {
            if (unit->is_cell_exist({x - unit_position.x, y - unit_position.y}) and
                unit->get_component({x - unit_position.x, y - unit_position.y}) !=
                nullptr) {
                continue;
            }
            if (this->blueprint->get_component({x, y}) ==
                nullptr) {
                continue;
            }
            if (this->blueprint_attachment_components.empty()) {
                continue;
            }
            if (this->blueprint->get_component({x, y}) !=
                                                                   this->blueprint_attachment_components[this->selected_blueprint_component_index]) {
                continue;
            }
            this->building_grid->set_mask_block({x, y},
                                                "selected_grid_block::selected_grid_block", this->preview_rotation,
                                                ctx);
        }
    }
    for (int i = 0; i < unit->components.size(); i++) {
        for (int y = 0; y < unit->grid_size.y; y++) {
            for (int x = 0; x < unit->grid_size.x; x++) {
                std::shared_ptr<BlueprintComponent> &component = unit->components[i];
                if (!this->blueprint->is_cell_exist({unit_position.x + x, unit_position.y + y})) {
                    continue;
                }
                if (component->get_block({x, y}).block_id == "empty_block::empty_block") {
                    continue;
                }
                if (this->blueprint->get_component({unit_position.x + x, unit_position.y + y}) ==
                    nullptr) {
                    BlueprintBlock block = component->get_block({x, y});
                    this->building_grid->set_preview_block({unit_position.x + x, unit_position.y + y},
                                                           block.block_id, this->preview_rotation, ctx);
                    if (i != this->selected_preview_component_index) {
                        this->building_grid->set_mask_block({unit_position.x + x, unit_position.y + y},
                                                            "discarded_block::discarded_block", this->preview_rotation,
                                                            ctx);
                    }
                    continue;
                }
                this->building_grid->set_mask_block({unit_position.x + x, unit_position.y + y},
                                                    "busy_grid_block::busy_grid_block", this->preview_rotation,
                                                    ctx);
            }
        }
    }

}

void Builder::clear_preview(EngineContext &ctx) {
    this->building_grid->clear_preview(ctx);
    this->building_grid->clear_mask(ctx);
}

int Builder::get_preview_rotation() {
    return this->preview_rotation;
}

sf::Vector2i &Builder::get_preview_position() {
    return this->preview_position;
}

void Builder::set_new_preview_position(sf::Vector2i position, EngineContext &ctx) {
    this->preview_position = position;
    this->find_blueprint_attachment_components();
    this->clear_preview(ctx);
    this->update_preview(ctx);
}

void Builder::rotate_preview(EngineContext &ctx) {
    this->preview_rotation = (this->preview_rotation + 1) % 4;
    this->find_blueprint_attachment_components();
    this->clear_preview(ctx);
    this->update_preview(ctx);
}

void Builder::select_next_preview_component(EngineContext &ctx) {
    std::shared_ptr<Blueprint> unit = this->blueprint_loader.lock()->create_blueprint(this->unit_id,
                                                                                      this->preview_rotation);

    this->selected_preview_component_index =
            (this->selected_preview_component_index + 1) % int(unit->components.size());
    this->find_blueprint_attachment_components();
    this->clear_preview(ctx);
    this->update_preview(ctx);
}


void Builder::select_next_blueprint_component(EngineContext &ctx) {
    if (this->blueprint_attachment_components.empty()) {
        return;
    }
    this->selected_blueprint_component_index =
            (this->selected_blueprint_component_index + 1) % int(this->blueprint_attachment_components.size());
    this->clear_preview(ctx);
    this->update_preview(ctx);
}

void Builder::find_blueprint_attachment_components() {
    this->selected_blueprint_component_index = 0;
    std::shared_ptr<Blueprint> unit = this->blueprint_loader.lock()->create_blueprint(this->unit_id,
                                                                                      this->preview_rotation);
    sf::Vector2i unit_position = {this->preview_position.x - unit->grid_size.x / 2,
                                  this->preview_position.y - unit->grid_size.y / 2};
    std::shared_ptr<BlueprintComponent> &selected_component = unit->components[this->selected_preview_component_index];

    std::vector<sf::Vector2i> bias = {{0,  1},
                                      {1,  0},
                                      {0,  -1},
                                      {-1, 0}};
    this->blueprint_attachment_components.clear();
    for (int y = 0; y < unit->grid_size.y; y++) {
        for (int x = 0; x < unit->grid_size.x; x++) {
            if (!this->blueprint->is_cell_exist({unit_position.x + x, unit_position.y + y})) {
                continue;
            }
            if (selected_component->get_block({x, y}).block_id == "empty_block::empty_block") {
                continue;
            }
            if (this->blueprint->get_component({unit_position.x + x, unit_position.y + y}) !=
                nullptr) {
                continue;
            }
            for (int i = 0; i < 4; i++) {
                sf::Vector2i block_position = sf::Vector2i({unit_position.x + x, unit_position.y + y}) + bias[i];
                if (!this->blueprint->is_cell_exist(block_position)) {
                    continue;
                }
                if (this->blueprint->get_component(block_position) ==
                    nullptr) {
                    continue;
                }
                if (unit->is_cell_exist({block_position.x - unit_position.x, block_position.y - unit_position.y}) and
                    unit->get_component({block_position.x - unit_position.x, block_position.y - unit_position.y}) !=
                    nullptr) {
                    continue;
                }
                this->blueprint_attachment_components.push_back(this->blueprint->get_component(block_position));
            }
        }
    }
    std::sort(this->blueprint_attachment_components.begin(), this->blueprint_attachment_components.end());
    auto last = std::unique(this->blueprint_attachment_components.begin(), this->blueprint_attachment_components.end());
    this->blueprint_attachment_components.erase(last, this->blueprint_attachment_components.end());
}