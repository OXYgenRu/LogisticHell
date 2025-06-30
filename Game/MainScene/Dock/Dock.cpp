//
// Created by EgorRychkov on 01.05.2025.
//

#include "Dock.h"
#include "../../../Engine/Application.h"
#include "EditorInterface/EditorInterface.h"
#include "../MainScene.h"

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
    node->interface->set_position({-ctx.app->get_window_size().x / 2, -ctx.app->get_window_size().y / 2});

    node->background = UI::Rectangle::create(node, ctx, 0);
    node->background->set_rectangle(-ctx.app->get_window_size() * 0.5f, ctx.app->get_window_size() * 0.5f);
    node->background->set_color(sf::Color(1, 2, 74));
}


std::shared_ptr<DockSpawner>
DockSpawner::create(const std::shared_ptr<Node> &parent, EngineContext &ctx, const std::shared_ptr<MainScene> &scene,
                    const sf::Vector2f &position, const sf::Vector2i &grid_size, float b2_block_side_size,
                    int render_priority) {
    auto node = std::make_shared<DockSpawner>(parent, render_priority);
    DockSpawner::setup(node, ctx, scene, position, grid_size, b2_block_side_size);
    parent->add_node(node);
    return node;
}

void DockSpawner::setup(const std::shared_ptr<DockSpawner> &node, EngineContext &ctx,
                        const std::shared_ptr<MainScene> &scene,
                        const sf::Vector2f &position, const sf::Vector2i &grid_size, float b2_block_side_size) {
    std::weak_ptr<MainScene> weak_scene = scene;
    std::weak_ptr<DockSpawner> weak_spawner = node;
    float sf_block_side_size = b2_block_side_size * scene->world->pixel_per_meter;
    node->scene = scene;
    node->position = position;
    node->grid_size = grid_size;
    node->b2_block_side_size = b2_block_side_size;

    node->set_position({position.x - sf_block_side_size / 2,
                        position.y - float(grid_size.y) * sf_block_side_size + sf_block_side_size / 2});

    node->text = Text::create(node, 1);
    node->text->set_text("Dock, position {x:" + std::to_string(position.x) + ",y:" + std::to_string(position.y) + "}");
//    node->text->set_text(
//            L"Dock, position {x:" + std::to_wstring(position.x) + L",y:" + std::to_wstring(position.y) + L"}");
    node->text->set_font("Minecraftia-Regular.ttf");
    node->text->set_character_size(24);
    node->text->set_scale(0.3);

    node->dock_area = UI::Button::create(node, ctx);
    node->dock_area->set_rectangle({0, 0},
                                   {float(grid_size.x) * sf_block_side_size,
                                    float(grid_size.y) * sf_block_side_size});
    node->dock_area->set_color(sf::Color(1, 56, 20));
    node->dock_area->bind_on_mouse_release([weak_spawner, weak_scene](sf::Event &event, EngineContext &ctx) {
        auto scene = weak_scene.lock();
        auto spawner = weak_spawner.lock();
        scene->world->delete_node(spawner->dock);
        spawner->dock = Dock::create(scene->world, ctx, scene->world, scene->world_camera,
                                     scene->structures_system, spawner->position,
                                     spawner->grid_size, spawner->b2_block_side_size,
                                     scene->blueprint_loader, 3);
        spawner->dock->interface->assemble_blueprint->bind_on_mouse_release(
                [weak_scene, weak_spawner](sf::Event &event, EngineContext &ctx) {
                    auto scene = weak_scene.lock();
                    auto spawner = weak_spawner.lock();
                    scene->structures_system->create_structure(spawner->dock->editor_controller->builder->blueprint,
                                                               spawner->dock->position, ctx);
                    scene->world->delete_node(spawner->dock);
                    spawner->dock = nullptr;
                    scene->world_camera->set_locked(false);
                });
        spawner->dock->interface->quit_dock->bind_on_mouse_release(
                [weak_scene, weak_spawner](sf::Event &event, EngineContext &ctx) {
                    auto scene = weak_scene.lock();
                    auto spawner = weak_spawner.lock();
                    scene->world->delete_node(spawner->dock);
                    spawner->dock = nullptr;
                    scene->world_camera->set_locked(false);
                });
        scene->world_camera->set_camera_target({0, 0});
        scene->world_camera->set_zoom(1);
    });
}