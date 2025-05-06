//
// Created by EgorRychkov on 01.05.2025.
//

#include "Dock.h"
#include "../Structure/Structure.h"
#include "Panel/DockPanel.h"

std::shared_ptr<Dock>
Dock::create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<World> world, sf::Vector2f position,
             sf::Vector2i grid_size, float b2_cell_size,
             EngineContext &ctx,
             int render_priority,
             int render_priority_layers) {
    auto node = std::make_shared<Dock>(parent, render_priority);
    node->set_render_layers_count(render_priority_layers + 1);
    Dock::setup(node, world, position, grid_size, b2_cell_size, ctx);
    parent->add_node(node);
    return node;
}


void Dock::setup(std::shared_ptr<Dock> node, std::shared_ptr<World> world, sf::Vector2f position,
                 sf::Vector2i grid_size, float b2_cell_size, EngineContext &ctx) {
    node->world = world;
    node->controller = DockController::create(node, node);
    node->panel = DockPanel::create(node, node, 1);
    node->camera = CameraNode::create(node, ctx);
    node->building_grid = BuildingGrid::create(node->camera, node, position, world->pixel_per_meter * b2_cell_size,
                                               b2_cell_size, grid_size);
    node->builder = Builder::create(node->building_grid);
    node->builder->set_default_blueprint();
    node->dock_collider = DockGridCollider::create(node->camera, node);
}

