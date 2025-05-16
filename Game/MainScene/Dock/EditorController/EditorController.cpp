//
// Created by EgorRychkov on 14.05.2025.
//

#include "EditorController.h"
#include "../../../../Engine/Application.h"

std::shared_ptr<EditorController>
EditorController::create(EngineContext &ctx, std::shared_ptr<Dock> dock,
                         std::shared_ptr<BuildingGrid> building_grid,
                         std::shared_ptr<BlueprintLoader> blueprint_loader) {
    auto node = std::make_shared<EditorController>(ctx, dock, building_grid, blueprint_loader);
    return node;
}

EditorController::EditorController(EngineContext &ctx, std::shared_ptr<Dock> dock,
                                   std::shared_ptr<BuildingGrid> building_grid,
                                   std::shared_ptr<BlueprintLoader> blueprint_loader) {
    this->dock = dock;
    this->builder = Builder::create(building_grid, blueprint_loader);
    this->builder->set_default_blueprint(ctx);
    this->editor_mode = EditorMode::Attachment;
}

void EditorController::on_mouse_release(sf::Event &event, EngineContext &ctx) {
    sf::Vector2i cell_position = this->get_grid_cell_position(ctx);
    switch (this->editor_mode) {
        case EditorMode::Attachment:
            this->builder->attach_unit(cell_position, ctx);
            break;
        case EditorMode::Destroying:
            this->builder->destroy_unit(cell_position, ctx);
            break;
    }

}

void EditorController::on_mouse_moved(sf::Event &event, EngineContext &ctx) {
    sf::Vector2i cell_position = this->get_grid_cell_position(ctx);

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

void EditorController::on_mouse_exit(EngineContext &ctx) {
    this->builder->clear_preview(ctx);
}

void EditorController::on_mouse_enter(EngineContext &ctx) {
    sf::Vector2i cell_position = this->get_grid_cell_position(ctx);
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

void EditorController::on_key_release(sf::Event &event, EngineContext &ctx) {
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
            if (event.key.code == sf::Keyboard::F) {
                this->editor_mode = EditorMode::Destroying;
            }
            break;
        case EditorMode::Destroying:
            if (event.key.code == sf::Keyboard::F) {
                this->editor_mode = EditorMode::Attachment;
            }
            break;
    }
}

sf::Vector2i EditorController::get_grid_cell_position(EngineContext &ctx) {
    float sf_cell_size = builder->building_grid->sf_cell_size;
    sf::Vector2i pixel_position = sf::Mouse::getPosition(*ctx.app->window);
    sf::Vector2f world_position = ctx.app->window->mapPixelToCoords(pixel_position);
    sf::Vector2f local_position = world_position - builder->building_grid->position;
    return {int((local_position.x + sf_cell_size / 2) / sf_cell_size),
            abs(int((local_position.y - sf_cell_size / 2) / sf_cell_size))};
}