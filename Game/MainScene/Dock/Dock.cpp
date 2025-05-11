//
// Created by EgorRychkov on 01.05.2025.
//

#include "Dock.h"
#include "../Structure/Structure.h"
#include "Panel/DockPanel.h"
#include "../../../Engine/Application.h"

std::shared_ptr<Dock>
Dock::create(std::shared_ptr<ContainerNode> parent, EngineContext &ctx, std::shared_ptr<World> world,
             sf::Vector2f position,
             sf::Vector2i grid_size, float b2_cell_size, std::shared_ptr<BlueprintLoader> blueprint_loader,
             std::shared_ptr<BlockFactory> block_factory,
             int render_priority,
             int render_priority_layers) {
    auto node = std::make_shared<Dock>(parent, render_priority);
    node->set_render_layers_count(render_priority_layers + 1);
    Dock::setup(node, ctx, world, position, grid_size, b2_cell_size, blueprint_loader, block_factory);
    parent->add_node(node);
    return node;
}


void Dock::setup(std::shared_ptr<Dock> node, EngineContext &ctx, std::shared_ptr<World> world, sf::Vector2f position,
                 sf::Vector2i grid_size, float b2_cell_size, std::shared_ptr<BlueprintLoader> blueprint_loader,
                 std::shared_ptr<BlockFactory> block_factory) {
    node->world = world;
    node->controller = DockController::create(node, node);
    node->background_collider = UICollider::create(node, 0);
    node->background_collider->vertices = {{0,                                   0},
                                           {float(ctx.app->window->getSize().x), 0},
                                           {float(ctx.app->window->getSize().x), float(ctx.app->window->getSize().y)},
                                           {0,                                   float(ctx.app->window->getSize().x)}};
    node->panel = DockPanel::create(node, node, 2);
    node->camera = CameraNode::create(node, ctx, 1);
    node->building_grid = BuildingGrid::create(node->camera, node, position, world->pixel_per_meter * b2_cell_size,
                                               b2_cell_size, grid_size, block_factory);
    node->builder = Builder::create(node->building_grid, blueprint_loader);
    node->builder->set_default_blueprint(ctx);
    node->dock_collider = DockGridCollider::create(node->camera, node);
}

