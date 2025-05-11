//
// Created by EgorRychkov on 04.05.2025.
//

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
    this->unit_mask_position = {0, 0};
}

void Builder::set_default_blueprint(EngineContext &ctx) {
    this->blueprint = std::make_shared<Blueprint>(this->building_grid->grid_size, false);
    this->blueprint->add_component()->get_block({0, 0}).block_id = "construction_block::construction_block";
    this->building_grid->clear(ctx);
    this->building_grid->set_block({0, 0}, "construction_block::construction_block", ctx);
}

void Builder::attach_unit(sf::Vector2i position, EngineContext &ctx) {
    if (!this->validate_unit_attachment(position)) {
        return;
    }
    std::shared_ptr<Blueprint> unit = this->blueprint_loader.lock()->create_blueprint(this->unit_id);
    std::shared_ptr<BlueprintComponent> unit_attachment_base = this->blueprint->get_component(
            position + this->attach_direction);
    std::shared_ptr<BlueprintComponent> unit_connecting_component = unit->get_component({0, 0});

    for (int y = 0; y < unit->grid_size.y; y++) {
        for (int x = 0; x < unit->grid_size.x; x++) {
            BlueprintBlock block = unit_connecting_component->get_block({x, y});
            if (block.block_id != "empty_block::empty_block") {
                unit_attachment_base->set_block({position.x + x, position.y + y}, block);
                this->building_grid->set_block({position.x + x, position.y + y}, block.block_id, ctx);
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
                    new_component->set_block({position.x + x, position.y + y}, block);
                    this->building_grid->set_block({position.x + x, position.y + y}, block.block_id, ctx);
                }
            }
        }
    }
}

bool Builder::validate_unit_attachment(sf::Vector2i position) {
    std::shared_ptr<Blueprint> unit = this->blueprint_loader.lock()->create_blueprint(this->unit_id);
    sf::Vector2i unit_attachment_base = position + this->attach_direction;
    if (unit_attachment_base.x < 0 or unit_attachment_base.x >= this->building_grid->grid_size.x) {
        return false;
    }
    if (unit_attachment_base.y < 0 or unit_attachment_base.y >= this->building_grid->grid_size.y) {
        return false;
    }

    if (this->blueprint->get_component(unit_attachment_base) == nullptr) {
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
            if (this->blueprint->get_component({position.x + x, position.y + y}) != nullptr) {
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


void Builder::update_mask(sf::Vector2i position, EngineContext &ctx) {
    this->unit_mask_position = position;
    std::shared_ptr<Blueprint> unit = this->blueprint_loader.lock()->create_blueprint(this->unit_id);
    for (auto &component: unit->components) {
        for (int y = 0; y < unit->grid_size.y; y++) {
            for (int x = 0; x < unit->grid_size.x; x++) {
                if (!this->blueprint->is_cell_exist({position.x + x, position.y + y})) {
                    continue;
                }
                if (component->get_block({x, y}).block_id == "empty_block::empty_block") {
                    continue;
                }
                if (this->blueprint->get_component({position.x + x, position.y + y}) == nullptr) {
                    BlueprintBlock block = component->get_block({x, y});
                    this->building_grid->set_mask_block({position.x + x, position.y + y}, block.block_id, ctx);
                    continue;
                }
                this->building_grid->set_mask_block({position.x + x, position.y + y},
                                                    "busy_grid_block::busy_grid_block",
                                                    ctx);

            }
        }
    }

}

void Builder::clear_mask(EngineContext &ctx) {
    this->building_grid->clear_mask(ctx);
}