//
// Created by EgorRychkov on 01.05.2025.
//

#include "Dock.h"
#include "../Structure/Structure.h"
#include "../../../Engine/Application.h"
#include "EditorInterface/EditorInterface.h"

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

    node->background_collider = UI::Collider::create(node, {0, 0}, {float(ctx.app->window->getSize().x),
                                                                    float(ctx.app->window->getSize().y)},
                                                     AnchorType::Absolute);
    node->background_collider->set_vertices({{0,                                   0},
                                             {float(ctx.app->window->getSize().x), 0},
                                             {float(ctx.app->window->getSize().x), float(ctx.app->window->getSize().y)},
                                             {0,                                   float(
                                                     ctx.app->window->getSize().x)}});


    node->camera = CameraNode::create(node, ctx, 1);
    node->controller = DockController::create(node, node);
    node->building_grid = BuildingGrid::create(node->camera, node, position, world->pixel_per_meter * b2_cell_size,
                                               b2_cell_size, grid_size, block_factory);
    node->editor_controller = EditorController::create(ctx, node, node->building_grid, blueprint_loader);
    node->interface = EditorInterface::create(node, ctx, node, 2);

    {
        node->blueprint_collider = UI::Collider::create(node->camera, {0, 0}, {float(ctx.app->window->getSize().x),
                                                                               float(ctx.app->window->getSize().y)},
                                                        AnchorType::Absolute, AnchorBinding::LeftUp, 1);
        node->blueprint_collider->bind_on_mouse_release([node](sf::Event &event, EngineContext &ctx) {
            node->editor_controller->on_mouse_release(event, ctx);
        });
        node->blueprint_collider->bind_on_mouse_moved([node](sf::Event &event, EngineContext &ctx) {
            node->editor_controller->on_mouse_moved(event, ctx);
        });
        node->blueprint_collider->bind_on_mouse_exit([node](EngineContext &ctx) {
            node->editor_controller->on_mouse_exit(ctx);
        });
        node->blueprint_collider->bind_on_mouse_enter([node](EngineContext &ctx) {
            node->editor_controller->on_mouse_enter(ctx);
        });
        float sf_cell_size = node->building_grid->b2_cell_size * world->pixel_per_meter;
        node->blueprint_collider->set_vertices({sf::Vector2f(
                node->building_grid->position.x - sf_cell_size / 2,
                node->building_grid->position.y + sf_cell_size / 2), sf::Vector2f(
                node->building_grid->position.x - sf_cell_size / 2,
                node->building_grid->position.y - float(node->building_grid->grid_size.y - 1) * sf_cell_size -
                sf_cell_size / 2), sf::Vector2f(
                node->building_grid->position.x + float(node->building_grid->grid_size.x - 1) * sf_cell_size +
                sf_cell_size / 2,
                node->building_grid->position.y - float(node->building_grid->grid_size.y - 1) * sf_cell_size -
                sf_cell_size / 2), sf::Vector2f(
                node->building_grid->position.x + float(node->building_grid->grid_size.x - 1) * sf_cell_size +
                sf_cell_size / 2,
                node->building_grid->position.y + sf_cell_size / 2)});
    }
}

