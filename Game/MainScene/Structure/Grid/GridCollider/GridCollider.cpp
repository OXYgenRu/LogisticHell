//
// Created by EgorRychkov on 29.04.2025.
//

#include "GridCollider.h"
#include "../../../../../Engine/Nodes/Base/ContainerNode.h"
#include "../../../../../Engine/Application.h"
#include "../Grid.h"
#include "../../Structure.h"

std::shared_ptr<GridCollider>
GridCollider::create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<Grid> grid, int render_priority) {
    auto node = std::make_shared<GridCollider>(parent, render_priority);
    GridCollider::setup(node, grid);
    parent->add_node(node);
    return node;
}

void GridCollider::setup(std::shared_ptr<GridCollider> node, std::shared_ptr<Grid> grid) {
    node->grid = grid;
    node->vertices.resize(4);
}

void GridCollider::update(EngineContext &ctx) {
    auto rigid_body = this->grid.lock()->structure.lock();
    for (int i = 0; i < 4; i++) {
        this->vertices[i] = rigid_body->sf_get_world_point(this->b2_vertices[i], ctx);
    }
}

void GridCollider::on_mouse_release(sf::Event &event, EngineContext &ctx) {
    sf::Vector2i pixel_pos = sf::Mouse::getPosition(*ctx.app->window);
    sf::Vector2f world_pos = ctx.app->window->mapPixelToCoords(pixel_pos);
    std::shared_ptr<Structure> structure = this->grid.lock()->structure.lock();
    b2Vec2 body_point = structure->b2_get_local_point(world_pos, ctx);
    sf::Vector2i block_position(
            {int((body_point.x + structure->grid->cell_size / 2) / structure->grid->cell_size),
             int((body_point.y + structure->grid->cell_size / 2) / structure->grid->cell_size)});
    if (!structure->grid->valid_block_attachment(block_position)) {
        return;
    }

    structure->grid->set_block(block_position);
}


