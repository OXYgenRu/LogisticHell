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
    this->unit_id = "construction_block";
    this->preview_position = {0, 0};
}

void Builder::set_default_blueprint(EngineContext &ctx) {
    this->blueprint = std::make_shared<Blueprint>(this->building_grid->grid_size, 0);
//    BlueprintBlock &default_block = this->blueprint->add_component()->get_block({0, 0});
//    default_block.type = BlockType::BusyAttachable;
//
//    std::shared_ptr<UnitProperties> standard_blueprint_properties = std::make_shared<UnitProperties>(nullptr);
//    standard_blueprint_properties->add_render_feature(
//            UnitRenderFeature("main_texture", "construction_block", {0, 0}, 0, {-0.5, -0.5}, {1, 1}, 0));
//    standard_blueprint_properties->add_unit_block({0, 0});
//    this->blueprint->set_unit_properties({0, 0}, standard_blueprint_properties);
//    this->blueprint->add_unit_properties(standard_blueprint_properties);
//    this->building_grid->add_render_feature(standard_blueprint_properties->get_render_features()[0], ctx);
    std::shared_ptr<Blueprint> unit = this->blueprint_loader.lock()->create_blueprint(this->unit_id,
                                                                                      this->preview_rotation);
    this->set_blueprint(unit, ctx);
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
            if (block.type == BlockType::Empty) {
                continue;
            }
            unit_attachment_base->set_block({unit_position.x + x, unit_position.y + y}, block);
        }
    }
    for (auto &component: unit->components) {
        if (component == unit_connecting_component) {
            continue;
        }
        std::shared_ptr<BlueprintComponent> new_component = this->blueprint->add_component();
        new_component->set_body_type(component->get_body_type());
        for (int y = 0; y < unit->grid_size.y; y++) {
            for (int x = 0; x < unit->grid_size.x; x++) {
                BlueprintBlock block = component->get_block({x, y});
                if (block.type == BlockType::Empty) {
                    continue;
                }
                new_component->set_block({unit_position.x + x, unit_position.y + y}, block);

            }
        }
    }
    for (auto &to: unit->get_units_properties()) {
        std::shared_ptr<UnitProperties> new_unit_properties = std::make_shared<UnitProperties>(unit_position, to,
                                                                                               to->rotation);
        blueprint->add_unit_properties(new_unit_properties);
        for (sf::Vector2i &block_position: new_unit_properties->get_unit_blocks()) {
            blueprint->set_unit_properties(block_position, new_unit_properties);
        }
        for (UnitRenderFeature &feature: new_unit_properties->get_render_features()) {
            if (!blueprint->is_cell_exist(feature.anchor_block)) {
                continue;
            }
            building_grid->add_render_feature(feature, ctx);
        }
    }
}

void Builder::destroy_unit(sf::Vector2i position, EngineContext &ctx) {
//    std::cout << "destroy_unit" << '\n';
    if (this->blueprint->get_component(position) == nullptr) {
        return;
    }
    std::shared_ptr<UnitProperties> deleting_unit_properties = blueprint->get_unit_properties(position);
    for (sf::Vector2i &block_position: deleting_unit_properties->get_unit_blocks()) {
        if (this->blueprint->get_component(block_position) != nullptr) {
            this->blueprint->get_component(block_position)->get_block(
                    block_position).type = BlockType::Empty;
            this->building_grid->set_mask("empty_block", block_position, ctx);
            this->building_grid->remove_features(block_position);
        }
    }
    for (int i = 0; i < blueprint->get_units_properties().size(); i++) {
        if (blueprint->get_units_properties()[i] == deleting_unit_properties) {
            blueprint->get_units_properties().erase(blueprint->get_units_properties().begin() + i);
        }
    }

}

bool Builder::validate_unit_attachment(sf::Vector2i position) {
//    std::cout << "validate_unit_attachment" << '\n';
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


void Builder::draw_building_preview(EngineContext &ctx) {
//    std::cout << "draw_building_preview" << '\n';
    std::shared_ptr<Blueprint> unit = this->blueprint_loader.lock()->create_blueprint(this->unit_id,
                                                                                      this->preview_rotation);
    sf::Vector2i unit_position = {this->preview_position.x - unit->grid_size.x / 2,
                                  this->preview_position.y - unit->grid_size.y / 2};

    std::vector<sf::Vector2i> bias = {{0,  1},
                                      {1,  0},
                                      {0,  -1},
                                      {-1, 0}};

    for (int y = 0; y < blueprint->grid_size.y; y++) {
        for (int x = 0; x < blueprint->grid_size.x; x++) {
            if (unit->is_cell_exist({x - unit_position.x, y - unit_position.y}) and
                unit->is_block_empty({x - unit_position.x, y - unit_position.y})) {
                continue;
            }
            if (this->blueprint->is_block_empty({x, y})) {
                continue;
            }
            if (this->blueprint_attachment_components.empty()) {
                continue;
            }
            if (this->blueprint->get_component({x, y}) !=
                this->blueprint_attachment_components[this->selected_blueprint_component_index]) {
                continue;
            }
            this->building_grid->set_mask("selected_grid_block", {x, y}, ctx);
        }
    }
    for (std::shared_ptr<UnitProperties> &properties: unit->get_units_properties()) {
        for (UnitRenderFeature &feature: properties->get_render_features()) {
            if (!blueprint->is_cell_exist({feature.anchor_block.x + unit_position.x,
                                           feature.anchor_block.y + unit_position.y})) {
                continue;
            }
            this->building_grid->add_preview_render_feature(feature, unit_position, ctx);
        }
    }
    for (std::shared_ptr<UnitProperties> &properties: unit->get_units_properties()) {
        for (sf::Vector2i &position: properties->get_unit_blocks()) {
            if (!blueprint->is_cell_exist({position.x + unit_position.x,
                                           position.y + unit_position.y})) {
                continue;
            }
            this->building_grid->set_mask("void_block", {position.x + unit_position.x,
                                                         position.y + unit_position.y}, ctx);
            if (unit->get_component(position) != unit->components[this->selected_preview_component_index]) {
                this->building_grid->set_mask("discarded_block", {position.x + unit_position.x,
                                                                  position.y + unit_position.y},
                                              ctx);
            }
            if (blueprint->get_component({position.x + unit_position.x,
                                          position.y + unit_position.y}) != nullptr) {
                this->building_grid->set_mask("busy_grid_block", {position.x + unit_position.x,
                                                                  position.y + unit_position.y},
                                              ctx);
            }
        }
    }
}

void Builder::draw_destroying_preview(EngineContext &ctx) {
//    std::cout << "draw_destroying_preview" << '\n';
    if (this->blueprint->is_block_empty(preview_position)) {
        return;
    }
    std::shared_ptr<UnitProperties> deleting_unit_properties = blueprint->get_unit_properties(this->preview_position);
    for (sf::Vector2i &block_position: deleting_unit_properties->get_unit_blocks()) {
        this->building_grid->set_mask("busy_grid_block", block_position, ctx);
    }
}


void Builder::clear_preview(EngineContext &ctx) {

    for (int y = 0; y < blueprint->grid_size.y; y++) {
        for (int x = 0; x < blueprint->grid_size.x; x++) {
            this->building_grid->remove_preview_features({x, y});
            if (this->blueprint->is_block_empty({x, y})) {
                this->building_grid->set_mask("empty_block", {x, y},
                                              ctx);
            } else {
                this->building_grid->set_mask("void_block", {x, y},
                                              ctx);
            }
        }
    }
}

int Builder::get_preview_rotation() {
    return this->preview_rotation;
}

sf::Vector2i &Builder::get_preview_position() {
    return this->preview_position;
}

void Builder::set_new_preview_position(sf::Vector2i position, EngineContext &ctx) {
    this->preview_position = position;

}

void Builder::rotate_preview(EngineContext &ctx) {
    this->preview_rotation = (this->preview_rotation + 1) % 4;
}

void Builder::select_next_preview_component(EngineContext &ctx) {
    std::shared_ptr<Blueprint> unit = this->blueprint_loader.lock()->create_blueprint(this->unit_id,
                                                                                      this->preview_rotation);

    this->selected_preview_component_index =
            (this->selected_preview_component_index + 1) % int(unit->components.size());
}


void Builder::select_next_blueprint_component(EngineContext &ctx) {
    if (this->blueprint_attachment_components.empty()) {
        return;
    }
    this->selected_blueprint_component_index =
            (this->selected_blueprint_component_index + 1) % int(this->blueprint_attachment_components.size());
}

void Builder::find_blueprint_attachment_components() {
//    std::cout << "find" << '\n';
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
            if (selected_component->get_block({x, y}).type == BlockType::Empty) {
                continue;
            }
            if (!this->blueprint->is_block_empty({unit_position.x + x, unit_position.y + y})) {
                continue;
            }
            if (unit->get_component({x, y}) != nullptr and
                unit->get_component({x, y})->get_block({x, y}).type != BlockType::BusyAttachable) {
                continue;
            }
            for (int i = 0; i < 4; i++) {
                sf::Vector2i block_position = sf::Vector2i({unit_position.x + x, unit_position.y + y}) + bias[i];
                if (!this->blueprint->is_cell_exist(block_position)) {
                    continue;
                }
                if (this->blueprint->is_block_empty(block_position)) {
                    continue;
                }
                if (unit->is_cell_exist({block_position.x - unit_position.x, block_position.y - unit_position.y}) and
                    unit->is_block_empty({block_position.x - unit_position.x, block_position.y - unit_position.y})) {
                    continue;
                }
                if (this->blueprint->get_component(block_position) != nullptr and
                    this->blueprint->get_component(block_position)->get_block(
                            block_position).type == BlockType::BusyAttachable) {
                    this->blueprint_attachment_components.push_back(
                            this->blueprint->get_component(block_position));
                }
            }
        }
    }
    std::sort(this->blueprint_attachment_components.begin(), this->blueprint_attachment_components.end());
    auto last = std::unique(this->blueprint_attachment_components.begin(), this->blueprint_attachment_components.end());
    this->blueprint_attachment_components.erase(last, this->blueprint_attachment_components.end());
}


void Builder::set_unit_id(const std::string &new_unit_id) {
    this->unit_id = new_unit_id;
    this->selected_preview_component_index = 0;
}


void Builder::set_blueprint(const std::shared_ptr<Blueprint> &new_blueprint, EngineContext &ctx) {
    for (int y = 0; y < blueprint->grid_size.y; y++) {
        for (int x = 0; x < blueprint->grid_size.x; x++) {
            this->building_grid->remove_features({x, y});
        }
    }
    blueprint = std::make_shared<Blueprint>(this->building_grid->grid_size, 0);
    for (auto &component: new_blueprint->components) {
        std::shared_ptr<BlueprintComponent> new_component = this->blueprint->add_component();
        new_component->set_body_type(component->get_body_type());
        for (int y = 0; y < new_blueprint->grid_size.y; y++) {
            for (int x = 0; x < new_blueprint->grid_size.x; x++) {
                BlueprintBlock block = component->get_block({x, y});
                if (block.type == BlockType::Empty) {
                    continue;
                }
                new_component->set_block({x, y}, block);

            }
        }
    }
    for (auto &to: new_blueprint->get_units_properties()) {
        std::shared_ptr<UnitProperties> new_unit_properties = std::make_shared<UnitProperties>(sf::Vector2i({0, 0}), to,
                                                                                               to->rotation);
        blueprint->add_unit_properties(new_unit_properties);
        for (sf::Vector2i &block_position: new_unit_properties->get_unit_blocks()) {
            blueprint->set_unit_properties(block_position, new_unit_properties);
        }
        for (UnitRenderFeature &feature: new_unit_properties->get_render_features()) {
            if (!blueprint->is_cell_exist(feature.anchor_block)) {
                continue;
            }
            building_grid->add_render_feature(feature, ctx);
        }
    }
}