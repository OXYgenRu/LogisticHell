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
    this->unit_index = 0;
    this->unit_id = "construction_block";
    this->preview_position = {0, 0};
}

void Builder::set_default_blueprint(EngineContext &ctx) {
    this->blueprint = std::make_shared<Blueprint>(this->building_grid->grid_size, true, 0);
    BlueprintBlock &default_block = this->blueprint->add_component()->get_block({0, 0});
    default_block.block_id = "construction_block::construction_block";

    std::shared_ptr<UnitProperties> standard_blueprint_properties = std::make_shared<UnitProperties>();
    standard_blueprint_properties->add_unit_block({0, 0});
    this->blueprint->set_unit_properties({0, 0}, standard_blueprint_properties);
    this->blueprint->add_unit_properties(standard_blueprint_properties);
    this->building_grid->set_default_state(ctx);
    this->building_grid->clear(ctx);
    this->building_grid->clear_background(ctx);
    this->building_grid->set_block({0, 0}, "construction_block::construction_block", 0, ctx);
}

void Builder::attach_unit(sf::Vector2i position, EngineContext &ctx) {
    std::cout << "attach_unit" << '\n';
    std::shared_ptr<Blueprint> unit = this->blueprint_loader.lock()->create_blueprint(this->unit_id,
                                                                                      this->preview_rotation);
    sf::Vector2i unit_position = {position.x - unit->grid_size.x / 2, position.y - unit->grid_size.y / 2};
    if (!this->validate_unit_attachment(unit_position)) {
        return;
    }
    this->blueprint->set_unit_properties(unit_position, unit->get_unit_properties({0, 0}));
    std::shared_ptr<BlueprintComponent> unit_attachment_base = this->blueprint_attachment_components[this->selected_blueprint_component_index];
    std::shared_ptr<BlueprintComponent> unit_connecting_component = unit->components[this->selected_preview_component_index];
    for (int y = 0; y < unit->grid_size.y; y++) {
        for (int x = 0; x < unit->grid_size.x; x++) {
            BlueprintBlock block = unit_connecting_component->get_block({x, y});
            if (block.block_id == "void_block::void_block" and block.background_block_id == "void_block::void_block") {
                continue;
            }
            if (block.block_id != "void_block::void_block") {

                this->building_grid->set_block({unit_position.x + x, unit_position.y + y}, block.block_id,
                                               block.rotation, ctx);

            }
            if (block.background_block_id != "void_block::void_block") {
                this->building_grid->set_background_block({unit_position.x + x, unit_position.y + y},
                                                          block.background_block_id,
                                                          block.rotation, ctx);
            }
            unit_attachment_base->set_block({unit_position.x + x, unit_position.y + y}, block);
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
                if (block.block_id == "void_block::void_block" and
                    block.background_block_id == "void_block::void_block") {
                    continue;
                }
                if (block.block_id != "void_block::void_block") {

                    this->building_grid->set_block({unit_position.x + x, unit_position.y + y}, block.block_id,
                                                   block.rotation, ctx);

                }
                if (block.background_block_id != "void_block::void_block") {
                    this->building_grid->set_background_block({unit_position.x + x, unit_position.y + y},
                                                              block.background_block_id,
                                                              block.rotation, ctx);
                }
                new_component->set_block({unit_position.x + x, unit_position.y + y}, block);

            }
        }
    }
    for (auto &to: unit->get_units_properties()) {
        std::shared_ptr<UnitProperties> new_unit_properties = std::make_shared<UnitProperties>(unit_position, to);
        blueprint->add_unit_properties(new_unit_properties);
        for (sf::Vector2i &block_position: new_unit_properties->get_unit_blocks()) {
            blueprint->set_unit_properties(block_position, new_unit_properties);
        }
    }
}

void Builder::destroy_unit(sf::Vector2i position, EngineContext &ctx) {
    std::cout << "destroy_unit" << '\n';
    if (this->blueprint->get_component(position, false) == nullptr and this->blueprint->get_component(position, true) ==
                                                                       nullptr) {
        return;
    }
    std::shared_ptr<UnitProperties> deleting_unit_properties = blueprint->get_unit_properties(position);
    for (sf::Vector2i &block_position: deleting_unit_properties->get_unit_blocks()) {
        if (this->blueprint->get_component(block_position, false) != nullptr) {
            BlueprintBlock &destroying_block = this->blueprint->get_component(block_position, false)->get_block(
                    block_position);
            destroying_block.block_id = "void_block::void_block";
            this->building_grid->set_block(block_position, "void_block::void_block", 0, ctx);
            this->building_grid->set_mask_block(block_position, "empty_block::empty_block", 0, ctx);
        }
        if (this->blueprint->get_component(block_position, true) != nullptr) {
            BlueprintBlock &destroying_block = this->blueprint->get_component(block_position, true)->get_block(
                    block_position);
            destroying_block.background_block_id = "void_block::void_block";
            this->building_grid->set_background_block(block_position, "void_block::void_block", 0, ctx);
            this->building_grid->set_mask_block(block_position, "empty_block::empty_block", 0, ctx);
        }
    }
    for (int i = 0; i < blueprint->get_units_properties().size(); i++) {
        if (blueprint->get_units_properties()[i] == deleting_unit_properties) {
            blueprint->get_units_properties().erase(blueprint->get_units_properties().begin() + i);
        }
    }

}

bool Builder::validate_unit_attachment(sf::Vector2i position) {
    std::cout << "validate_unit_attachment" << '\n';
    std::shared_ptr<Blueprint> unit = this->blueprint_loader.lock()->create_blueprint(this->unit_id,
                                                                                      this->preview_rotation);
    if (this->blueprint_attachment_components.empty()) {
        return false;
    }
    for (int y = 0; y < unit->grid_size.y; y++) {
        for (int x = 0; x < unit->grid_size.x; x++) {
            if (unit->get_component({x, y}, false) == nullptr and
                unit->get_component({x, y}, true) == nullptr) {
                continue;
            }
            if (!this->blueprint->is_cell_exist({position.x + x, position.y + y})) {
                return false;
            }
            if (this->blueprint->get_component({position.x + x, position.y + y}, false) != nullptr and
                unit->get_component({x, y}, false) != nullptr) {
                return false;
            }
            if (this->blueprint->get_component({position.x + x, position.y + y}, true) != nullptr and
                unit->get_component({x, y}, true) != nullptr) {
                return false;
            }
        }
    }
    return true;
}


void Builder::draw_building_preview(EngineContext &ctx) {
    std::cout << "draw_building_preview" << '\n';
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
            if (this->blueprint->get_component({x, y}, false) !=
                this->blueprint_attachment_components[this->selected_blueprint_component_index] and
                this->blueprint->get_component({x, y}, true) !=
                this->blueprint_attachment_components[this->selected_blueprint_component_index]) {
                continue;
            }
            this->building_grid->set_mask_block({x, y},
                                                "selected_grid_block::selected_grid_block", 0,
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
                if (component->get_block({x, y}).block_id == "void_block::void_block" and
                    component->get_block({x, y}).background_block_id == "void_block::void_block") {
                    continue;
                }
                if (this->blueprint->is_block_empty({unit_position.x + x, unit_position.y + y})) {
                    BlueprintBlock block = component->get_block({x, y});
                    if (block.block_id != "void_block::void_block") {
                        this->building_grid->set_preview_block({unit_position.x + x, unit_position.y + y},
                                                               block.block_id, block.rotation, ctx);
                        this->building_grid->set_mask_block({unit_position.x + x, unit_position.y + y},
                                                            "void_block::void_block", this->preview_rotation,
                                                            ctx);
                    }
                    if (block.background_block_id != "void_block::void_block") {
                        this->building_grid->set_background_preview_block({unit_position.x + x, unit_position.y + y},
                                                                          block.background_block_id, block.rotation,
                                                                          ctx);
                        this->building_grid->set_mask_block({unit_position.x + x, unit_position.y + y},
                                                            "void_block::void_block", this->preview_rotation,
                                                            ctx);
                    }
                    if (i != this->selected_preview_component_index) {
                        this->building_grid->set_mask_block({unit_position.x + x, unit_position.y + y},
                                                            "discarded_block::discarded_block", 0,
                                                            ctx);
                    }
                    continue;
                }
                this->building_grid->set_mask_block({unit_position.x + x, unit_position.y + y},
                                                    "busy_grid_block::busy_grid_block", 0,
                                                    ctx);

            }
        }
    }
}

void Builder::draw_destroying_preview(EngineContext &ctx) {
    std::cout << "draw_destroying_preview" << '\n';
    if (this->blueprint->is_block_empty(preview_position)) {
        return;
    }
    std::shared_ptr<UnitProperties> deleting_unit_properties = blueprint->get_unit_properties(this->preview_position);
    for (sf::Vector2i &block_position: deleting_unit_properties->get_unit_blocks()) {
        this->building_grid->set_mask_block(block_position,
                                            "busy_grid_block::busy_grid_block", 0,
                                            ctx);
    }
}


void Builder::clear_preview(EngineContext &ctx) {
    this->building_grid->clear_background_preview(ctx);
    this->building_grid->clear_preview(ctx);

    for (int y = 0; y < blueprint->grid_size.y; y++) {
        for (int x = 0; x < blueprint->grid_size.x; x++) {
            if (this->blueprint->is_block_empty({x, y})) {
                this->building_grid->set_mask_block({x, y},
                                                    "empty_block::empty_block", this->preview_rotation,
                                                    ctx);
            } else {
                this->building_grid->set_mask_block({x, y},
                                                    "void_block::void_block", this->preview_rotation,
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
    std::cout << "find" << '\n';
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
            if (selected_component->get_block({x, y}).block_id == "void_block::void_block") {
                continue;
            }
            if (!this->blueprint->is_block_empty({unit_position.x + x, unit_position.y + y})) {
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
                    !unit->is_block_empty({block_position.x - unit_position.x, block_position.y - unit_position.y})) {
                    continue;
                }
                if (this->blueprint->get_component(block_position, false) != nullptr and
                    this->blueprint->get_component(block_position, false)->get_block(
                            block_position).allow_attachments) {
                    this->blueprint_attachment_components.push_back(
                            this->blueprint->get_component(block_position, false));
                }
                if (this->blueprint->get_component(block_position, true) != nullptr and
                    this->blueprint->get_component(block_position, true)->get_block(
                            block_position).allow_attachments) {
                    this->blueprint_attachment_components.push_back(
                            this->blueprint->get_component(block_position, true));
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