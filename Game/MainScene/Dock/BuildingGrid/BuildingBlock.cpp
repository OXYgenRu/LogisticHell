//
// Created by EgorRychkov on 03.05.2025.
//

#include "BuildingBlock.h"

std::shared_ptr<BuildingBlock>
BuildingBlock::create(std::shared_ptr<ContainerNode> parent, EngineContext &ctx, sf::Vector2i cell_position,
                      float sf_cell_size, int rotation, const std::string &texture_name,
                      int render_priority,
                      int render_priority_layers) {
    auto node = std::make_shared<BuildingBlock>(parent, render_priority);
    node->set_render_layers_count(render_priority_layers + 1);
    BuildingBlock::setup(node, ctx, cell_position, sf_cell_size, rotation, texture_name);
    parent->add_node(node);
    return node;
}

void BuildingBlock::setup(std::shared_ptr<BuildingBlock> node, EngineContext &ctx, sf::Vector2i cell_position,
                          float sf_cell_size, int rotation,
                          const std::string &texture_name) {
    node->vertices.resize(4);
    node->set_position(sf::Vector2f(float(cell_position.x), float(cell_position.y)) * sf_cell_size);
    node->vertices[0] = sf::Vector2f(-sf_cell_size / 2, sf_cell_size / 2);
    node->vertices[1] = sf::Vector2f(-sf_cell_size / 2, -sf_cell_size / 2);
    node->vertices[2] = sf::Vector2f(sf_cell_size / 2, -sf_cell_size / 2);
    node->vertices[3] = sf::Vector2f(sf_cell_size / 2, sf_cell_size / 2);

    node->textured_quad = TexturedQuad::create(node);
    node->textured_quad->set_texture(texture_name, rotation, ctx);
    node->textured_quad->set_quad(node->vertices);
}