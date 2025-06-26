//
// Created by EgorRychkov on 27.04.2025.
//

#include "TexturedQuad.h"
#include "../../Base/Node.h"
#include "../../../Application.h"

std::shared_ptr<TexturedQuad>
TexturedQuad::create(const std::shared_ptr<Node> &parent, int render_priority) {
    auto node = std::make_shared<TexturedQuad>(parent, render_priority);
    TexturedQuad::setup(node);
    parent->add_node(node);
    return node;
}

void TexturedQuad::setup(std::shared_ptr<TexturedQuad> node) {
    node->quad.resize(4);
    node->quad.setPrimitiveType(sf::Quads);
}

void TexturedQuad::render(EngineContext &ctx, sf::RenderStates &states) {
    ctx.app->batch->add_vertices(quad, states.transform);
}

void TexturedQuad::update(EngineContext &ctx) {

}

void TexturedQuad::set_texture(const std::string &new_texture_name, int rotation, EngineContext &ctx) {
    std::vector<sf::Vector2f> vertices = ctx.app->texture_atlas->get_region(new_texture_name).get_rect();
    for (int i = 0; i < 4; i++) {
        this->quad[(i + rotation) % 4].texCoords = vertices[i];
    }

}

void TexturedQuad::set_quad(const std::vector<sf::Vector2f> &vertices) {
    for (int i = 0; i < 4; i++) {
        this->quad[i].position = vertices[i];
    }
}