//
// Created by EgorRychkov on 03.05.2025.
//

#include "BuildingBlock.h"

std::shared_ptr<BuildingBlock>
BuildingBlock::create(const std::shared_ptr<Node> &parent, EngineContext &ctx, sf::Vector2i cell_position,
                      float sf_cell_size, int rotation, const std::string &texture,
                      int render_priority) {
    auto node = std::make_shared<BuildingBlock>(parent, render_priority);
    BuildingBlock::setup(node, ctx, cell_position, sf_cell_size, rotation, texture);
    parent->add_node(node);
    return node;
}

void BuildingBlock::setup(std::shared_ptr<BuildingBlock> node, EngineContext &ctx, sf::Vector2i cell_position,
                          float sf_cell_size, int rotation,
                          const std::string &texture) {
    node->vertices.resize(4);
    node->set_position(
            sf::Vector2f(float(cell_position.x) - 0.5f, float(cell_position.y) - 0.5f) *
            sf_cell_size);
    node->vertices[0] = sf::Vector2f(0, sf_cell_size);
    node->vertices[1] = sf::Vector2f(0, 0);
    node->vertices[2] = sf::Vector2f(sf_cell_size, 0);
    node->vertices[3] = sf::Vector2f(sf_cell_size, sf_cell_size);

    node->textured_quad = TexturedQuad::create(node);
    node->textured_quad->set_texture(texture, rotation, ctx);
    node->textured_quad->set_quad(node->vertices);
}