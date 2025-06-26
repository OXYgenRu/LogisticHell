//
// Created by EgorRychkov on 01.05.2025.
//

#include "Dock.h"
#include "../../../Engine/Application.h"
#include "EditorInterface/EditorInterface.h"

std::shared_ptr<Dock>
Dock::create(const std::shared_ptr<Node> &parent, EngineContext &ctx, const std::shared_ptr<World> &world,
             const std::shared_ptr<CameraNode> &world_camera,
             const std::shared_ptr<StructuresSystem> &structures_system,
             sf::Vector2f position,
             sf::Vector2i grid_size, float b2_cell_size, const std::shared_ptr<BlueprintLoader> &blueprint_loader,
             int render_priority) {
    auto node = std::make_shared<Dock>(parent, render_priority);
    Dock::setup(node, ctx, world, world_camera, structures_system, position, grid_size, b2_cell_size, blueprint_loader);
    parent->add_node(node);
    return node;
}


void Dock::setup(const std::shared_ptr<Dock> &node, EngineContext &ctx, const std::shared_ptr<World> &world,
                 const std::shared_ptr<CameraNode> &world_camera,
                 const std::shared_ptr<StructuresSystem> &structures_system,
                 sf::Vector2f position,
                 sf::Vector2i grid_size, float b2_cell_size, const std::shared_ptr<BlueprintLoader> &blueprint_loader) {
    world_camera->set_locked(true);
    std::weak_ptr<Dock> weak_dock = node;
    node->position = position;
    node->structures_system = structures_system;
    node->world = world;
    node->camera = CameraNode::create(node, ctx, 1);

    node->controller = DockController::create(node, node);

    node->building_grid = BuildingGrid::create(node->camera, ctx, world->pixel_per_meter * b2_cell_size, grid_size);

    {
        node->building_grid->grid_collider->bind_on_mouse_release(
                [weak_dock](sf::Event &event, EngineContext &ctx, const sf::Vector2f &local_position) {
                    weak_dock.lock()->editor_controller->on_mouse_release(event, ctx, local_position);
                });
        node->building_grid->grid_collider->bind_on_mouse_moved(
                [weak_dock](sf::Event &event, EngineContext &ctx, const sf::Vector2f &local_position) {
                    weak_dock.lock()->editor_controller->on_mouse_moved(event, ctx, local_position);
                });
        node->building_grid->grid_collider->bind_on_mouse_exit(
                [weak_dock](EngineContext &ctx, const sf::Vector2f &local_position) {
                    weak_dock.lock()->editor_controller->on_mouse_exit(ctx, local_position);
                });
        node->building_grid->grid_collider->bind_on_mouse_enter(
                [weak_dock](EngineContext &ctx, const sf::Vector2f &local_position) {
                    weak_dock.lock()->editor_controller->on_mouse_enter(ctx, local_position);
                });
    }
    node->editor_controller = EditorController::create(ctx, node, node->building_grid, blueprint_loader);

    node->interface = EditorInterface::create(node, ctx, node, blueprint_loader, 20);
    {
        node->interface->set_position({-ctx.app->get_window_size().x / 2, -ctx.app->get_window_size().y / 2});
    }
    node->background = UI::Rectangle::create(node, ctx, 0);
    node->background->set_rectangle(-ctx.app->get_window_size() * 0.5f, ctx.app->get_window_size() * 0.5f);
    node->background->set_color(sf::Color(1, 2, 74));
}

