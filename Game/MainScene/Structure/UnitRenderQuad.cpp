//
// Created by EgorRychkov on 16.06.2025.
//

#include "UnitRenderQuad.h"
#include "../../../Engine/Application.h"

std::shared_ptr<UnitRenderQuad>
UnitRenderQuad::create(const std::shared_ptr<Node> &parent, EngineContext &ctx, const std::string &texture_name,
                       const sf::Vector2i &anchor_block,
                       const sf::Vector2f &position, const std::vector<sf::Vector2f> &vertices, float angle,
                       float sf_block_side_size,
                       int render_priority) {
    auto node = std::make_shared<UnitRenderQuad>(parent, render_priority);
    TexturedQuad::setup(node);
    UnitRenderQuad::setup(node, ctx, texture_name, anchor_block, position, vertices, angle, sf_block_side_size);
    parent->add_node(node);
    return node;
}

void
UnitRenderQuad::setup(const std::shared_ptr<UnitRenderQuad> &node, EngineContext &ctx, const std::string &texture_name,
                      const sf::Vector2i &anchor_block, const sf::Vector2f &position,
                      const std::vector<sf::Vector2f> &vertices, float angle, float sf_block_side_size) {
    node->set_texture(texture_name, 0, ctx);
    std::vector<sf::Vector2f> new_vertices(4);
    for (int i = 0; i < 4; i++) {
        new_vertices[i] = {vertices[i].x * sf_block_side_size, -vertices[i].y * sf_block_side_size};
    }
    node->set_quad(new_vertices);
    node->feature_transform.translate({position.x * sf_block_side_size, -position.y * sf_block_side_size});
    node->feature_transform.rotate(angle);
    node->set_position({float(anchor_block.x) * sf_block_side_size, float(anchor_block.y) * sf_block_side_size});
}

void UnitRenderQuad::render(EngineContext &ctx, sf::RenderStates &states) {
    ctx.app->batch->set_texture(*ctx.app->texture_atlas->get_texture(), ctx);
    ctx.app->batch->add_vertices(this->quad, states.transform * this->feature_transform);
}