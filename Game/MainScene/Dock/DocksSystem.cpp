//
// Created by EgorRychkov on 13.07.2025.
//

#include "DocksSystem.h"
#include "../MainScene.h"

std::shared_ptr<DocksSystem>
DocksSystem::create(const std::shared_ptr<Node> &parent, const std::shared_ptr<MainScene> &scene,
                    const std::string &node_id, int render_priority) {
    auto node = std::make_shared<DocksSystem>(parent, node_id, render_priority);
    parent->add_node(node);
    DocksSystem::setup(node, scene);
    return node;
}

void DocksSystem::setup(const std::shared_ptr<DocksSystem> &node, const std::shared_ptr<MainScene> &scene) {
    node->weak_scene = scene;
}

void DocksSystem::create_dock_spawner(EngineContext &ctx, const sf::Vector2f &position, const sf::Vector2i &grid_size,
                                      float b2_block_side_size) {
    auto scene = weak_scene.lock();
    this->spawners.push_back(
            DockSpawner::create(scene->world, ctx, scene, position, grid_size, b2_block_side_size, "DockSpawner"));
}

void DocksSystem::spawn_dock(EngineContext &ctx, const sf::Vector2f &position, const sf::Vector2i &grid_size,
                             float b2_block_side_size, const std::shared_ptr<Blueprint> &blueprint) {
    auto capture_weak_scene = this->weak_scene;
    auto scene = this->weak_scene.lock();
    scene->delete_node(this->dock);
    this->dock = Dock::create(scene, ctx, scene->world, scene->world_camera,
                              scene->structures_system, position,
                              grid_size, b2_block_side_size,
                              scene->blueprint_loader, "Dock", 5);
    this->dock->interface->assemble_blueprint->bind_on_mouse_release(
            [capture_weak_scene](sf::Event &event, EngineContext &ctx) {
                auto scene = capture_weak_scene.lock();
                scene->structures_system->create_structure(
                        scene->docks_system->dock->editor_controller->builder->blueprint,
                        scene->docks_system->dock->position, ctx);
                scene->delete_node(scene->docks_system->dock);
                scene->docks_system->dock = nullptr;
                scene->world_camera->set_locked(false);
            });
    this->dock->interface->quit_dock->bind_on_mouse_release(
            [capture_weak_scene](sf::Event &event, EngineContext &ctx) {
                auto scene = capture_weak_scene.lock();
                scene->delete_node(scene->docks_system->dock);
                scene->docks_system->dock = nullptr;
                scene->world_camera->set_locked(false);
            });
    if (blueprint != nullptr) {
        this->dock->editor_controller->builder->set_blueprint(blueprint, ctx);
    }
    scene->world_camera->set_camera_target({0, 0});
    scene->world_camera->set_zoom(1);
}


std::shared_ptr<DockSpawner> DocksSystem::find_nearest_dock(const sf::Vector2f &position) {
    auto scene = weak_scene.lock();
    float pixel_per_meter = scene->world->pixel_per_meter;
    std::vector<std::pair<float, std::shared_ptr<DockSpawner>>> distances;
    for (auto &spawner: spawners) {
        sf::Vector2f spawner_center_position = spawner->get_dock_position();
        sf::Vector2f dock_size = {float(spawner->get_grid_size().x) * pixel_per_meter * spawner->get_block_side_size(),
                                  float(spawner->get_grid_size().y) * pixel_per_meter * spawner->get_block_side_size()};
        spawner_center_position += dock_size * 0.5f;
        distances.emplace_back((spawner_center_position.x - position.x) * (spawner_center_position.x - position.x) +
                               (spawner_center_position.y - position.y) * (spawner_center_position.y - position.y),
                               spawner);
    }
    std::sort(distances.begin(), distances.end());
    return distances.begin()->second;
}