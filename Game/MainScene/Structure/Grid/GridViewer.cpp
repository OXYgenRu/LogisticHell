//
// Created by EgorRychkov on 28.04.2025.
//

#include "GridViewer.h"
#include "../../../../Engine/Nodes/Base/ContainerNode.h"
#include "../Structure.h"

std::shared_ptr<GridViewer>
GridViewer::create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<Grid> grid, b2Vec2 grid_position,
                   float cell_size,
                   int render_priority) {
    auto node = std::make_shared<GridViewer>(parent, render_priority);
    TexturedQuad::setup(node);
    GridViewer::setup(node, grid, grid_position, cell_size);
    parent->add_node(node);
    return node;
}

void
GridViewer::setup(std::shared_ptr<GridViewer> node, std::shared_ptr<Grid> grid, b2Vec2 grid_position, float cell_size) {
    node->texture.loadFromFile("blocks/EmptyGridBlockBlue.png");
    node->quad[0].texCoords = sf::Vector2f(0.f, 0.f);
    node->quad[1].texCoords = sf::Vector2f(0.f, node->texture.getSize().y);
    node->quad[2].texCoords = sf::Vector2f(node->texture.getSize().x,
                                           node->texture.getSize().y);
    node->quad[3].texCoords = sf::Vector2f(node->texture.getSize().x, 0.f);

    node->vertices[0] = {grid_position.x * cell_size + -cell_size / 2, cell_size / 2 + grid_position.y * cell_size};
    node->vertices[1] = {grid_position.x * cell_size + -cell_size / 2, -cell_size / 2 + grid_position.y * cell_size};
    node->vertices[2] = {grid_position.x * cell_size + cell_size / 2, -cell_size / 2 + grid_position.y * cell_size};
    node->vertices[3] = {grid_position.x * cell_size + cell_size / 2, cell_size / 2 + grid_position.y * cell_size};

    node->grid = grid;
}


void GridViewer::update(EngineContext &ctx) {
    auto body = this->grid.lock()->structure.lock();
    for (int i = 0; i < this->quad.getVertexCount(); i++) {
        this->quad[i].position = body->sf_get_world_point(this->vertices[i], ctx);
    }
}