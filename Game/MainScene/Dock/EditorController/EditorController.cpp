//
// Created by EgorRychkov on 14.05.2025.
//

#include "EditorController.h"
#include "../../../../Engine/Application.h"

std::shared_ptr<EditorController>
EditorController::create(EngineContext &ctx, const std::shared_ptr<Dock> &dock,
                         const std::shared_ptr<BuildingGrid> &building_grid,
                         const std::shared_ptr<GameWorld> &world) {
    auto node = std::make_shared<EditorController>(ctx, dock, building_grid, world);
    return node;
}

EditorController::EditorController(EngineContext &ctx, const std::shared_ptr<Dock> &dock,
                                   const std::shared_ptr<BuildingGrid> &building_grid,
                                   const std::shared_ptr<GameWorld> &world) {
    this->dock = dock;
    this->builder = Builder::create(building_grid, world);
    this->builder->set_default_blueprint(ctx);
    this->editor_mode = EditorMode::Attachment;
    this->is_preview_active = false;
}

void EditorController::on_mouse_release(sf::Event &event, EngineContext &ctx, const sf::Vector2f &local_position) {
    sf::Vector2i cell_position = this->get_grid_cell_position(ctx, local_position);
    switch (this->editor_mode) {
        case EditorMode::Attachment:
            this->builder->attach_unit(cell_position, ctx);
            this->builder->find_blueprint_attachment_components();
            this->builder->clear_preview(ctx);
            this->builder->draw_building_preview(ctx);
            break;
        case EditorMode::Destroying:
            this->builder->destroy_unit(cell_position, ctx);
            this->builder->clear_preview(ctx);
            this->builder->draw_destroying_preview(ctx);
            break;
    }

}

void EditorController::on_mouse_moved(sf::Event &event, EngineContext &ctx, const sf::Vector2f &local_position) {
    sf::Vector2i cell_position = this->get_grid_cell_position(ctx, local_position);

    switch (this->editor_mode) {
        case EditorMode::Attachment:
            if (cell_position != builder->get_preview_position()) {
                this->builder->set_new_preview_position(cell_position, ctx);
                this->builder->find_blueprint_attachment_components();
                this->builder->clear_preview(ctx);
                this->builder->draw_building_preview(ctx);
            }
            break;
        case EditorMode::Destroying:
            if (cell_position != builder->get_preview_position()) {
                this->builder->set_new_preview_position(cell_position, ctx);
                this->builder->clear_preview(ctx);
                this->builder->draw_destroying_preview(ctx);
            }
            break;
    }
}

void EditorController::on_mouse_exit(EngineContext &ctx, const sf::Vector2f &local_position) {
    this->builder->clear_preview(ctx);
    this->is_preview_active = false;
}

void EditorController::on_mouse_enter(EngineContext &ctx, const sf::Vector2f &local_position) {
    sf::Vector2i cell_position = this->get_grid_cell_position(ctx, local_position);
    this->is_preview_active = true;
    switch (this->editor_mode) {
        case EditorMode::Attachment:
            this->builder->set_new_preview_position(cell_position, ctx);
            this->builder->find_blueprint_attachment_components();
            this->builder->clear_preview(ctx);
            this->builder->draw_building_preview(ctx);
            break;
        case EditorMode::Destroying:
            this->builder->set_new_preview_position(cell_position, ctx);
            this->builder->clear_preview(ctx);
            this->builder->draw_destroying_preview(ctx);
            break;
    }
}

void EditorController::on_key_release(sf::Event &event, EngineContext &ctx) {
    if (!is_preview_active) {
        return;
    }
    switch (this->editor_mode) {
        case EditorMode::Attachment:
            if (event.key.code == sf::Keyboard::E) {
                this->builder->select_next_preview_component(ctx);
                this->builder->find_blueprint_attachment_components();
                this->builder->clear_preview(ctx);
                this->builder->draw_building_preview(ctx);
            }
            if (event.key.code == sf::Keyboard::Q) {
                this->builder->select_next_blueprint_component(ctx);
                this->builder->clear_preview(ctx);
                this->builder->draw_building_preview(ctx);
            }
            if (event.key.code == sf::Keyboard::R) {
                this->builder->rotate_preview(ctx);
                this->builder->find_blueprint_attachment_components();
                this->builder->clear_preview(ctx);
                this->builder->draw_building_preview(ctx);
            }
            break;
        case EditorMode::Destroying:
            break;
    }
}

void EditorController::set_mode(const EditorMode &new_mode, EngineContext &ctx) {
    this->editor_mode = new_mode;
    if (!is_preview_active) {
        return;
    }
    switch (new_mode) {
        case EditorMode::Attachment:
            this->builder->find_blueprint_attachment_components();
            this->builder->clear_preview(ctx);
            this->builder->draw_building_preview(ctx);
            break;
        case EditorMode::Destroying:
            this->builder->clear_preview(ctx);
            this->builder->draw_destroying_preview(ctx);
            break;
    }
}

sf::Vector2i EditorController::get_grid_cell_position(EngineContext &ctx, const sf::Vector2f &local_position) {
    float sf_cell_size = builder->building_grid->sf_cell_size;
    return {int((local_position.x) / sf_cell_size),
            abs(builder->building_grid->grid_size.y - int((local_position.y) / sf_cell_size) - 1)};
}

void EditorController::set_unit(const unsigned int &unit_index, EngineContext &ctx) {
    this->builder->set_unit_index(unit_index);
    this->editor_mode = EditorMode::Attachment;
}