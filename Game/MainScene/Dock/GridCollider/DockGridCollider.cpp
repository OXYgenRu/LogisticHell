//
// Created by EgorRychkov on 01.05.2025.
//

#include "DockGridCollider.h"
#include "../../../../Engine/Nodes/Base/ContainerNode.h"
#include "../Dock.h"
#include "../../../../Engine/Application.h"
#include "../../Structure/Structure.h"

std::shared_ptr<DockGridCollider>
DockGridCollider::create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<Dock> dock,
                         int render_priority) {
    auto node = std::make_shared<DockGridCollider>(parent, render_priority);
    DockGridCollider::setup(node, dock);
    parent->add_node(node);
    return node;

}

void DockGridCollider::setup(std::shared_ptr<DockGridCollider> node, std::shared_ptr<Dock> dock) {
    node->dock = dock;
    float sf_cell_size = dock->building_grid->b2_cell_size * dock->world.lock()->pixel_per_meter;
    node->vertices.resize(4);
    node->vertices[0] = sf::Vector2f(
            dock->building_grid->position.x - sf_cell_size / 2,
            dock->building_grid->position.y + sf_cell_size / 2);
    node->vertices[1] = sf::Vector2f(
            dock->building_grid->position.x - sf_cell_size / 2,
            dock->building_grid->position.y - float(dock->building_grid->grid_size.y - 1) * sf_cell_size -
            sf_cell_size / 2);
    node->vertices[2] = sf::Vector2f(
            dock->building_grid->position.x + float(dock->building_grid->grid_size.x - 1) * sf_cell_size +
            sf_cell_size / 2,
            dock->building_grid->position.y - float(dock->building_grid->grid_size.y - 1) * sf_cell_size -
            sf_cell_size / 2);
    node->vertices[3] = sf::Vector2f(
            dock->building_grid->position.x + float(dock->building_grid->grid_size.x - 1) * sf_cell_size +
            sf_cell_size / 2,
            dock->building_grid->position.y + sf_cell_size / 2);
}

void DockGridCollider::on_mouse_release(sf::Event &event, EngineContext &ctx) {
    float sf_cell_size = dock.lock()->building_grid->sf_cell_size;
    sf::Vector2i pixel_pos = sf::Mouse::getPosition(*ctx.app->window);
    sf::Vector2f world_pos = ctx.app->window->mapPixelToCoords(pixel_pos);
    sf::Vector2f local_pos = world_pos - this->dock.lock()->building_grid->position;
    sf::Vector2i cell_pos = {int((local_pos.x + sf_cell_size / 2) / sf_cell_size),
                             abs(int((local_pos.y - sf_cell_size / 2) / sf_cell_size))};
    auto builder = dock.lock()->builder;
    builder->attach_block(cell_pos);

}