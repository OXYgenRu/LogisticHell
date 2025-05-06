//
// Created by EgorRychkov on 27.04.2025.
//

#include "TexturedQuad.h"
#include "../../Base/ContainerNode.h"
#include "../../../Application.h"

std::shared_ptr<TexturedQuad>
TexturedQuad::create(std::shared_ptr<ContainerNode> parent, int render_priority) {
    auto node = std::make_shared<TexturedQuad>(parent, render_priority);
    TexturedQuad::setup(node);
    parent->add_node(node);
    return node;
}

void TexturedQuad::setup(std::shared_ptr<TexturedQuad> node) {
    node->quad.resize(4);
    node->quad.setPrimitiveType(sf::Quads);
}

void TexturedQuad::render(EngineContext &ctx) {
    ctx.app->window->draw(quad, ctx.app->texture_atlas->get_texture());
}

void TexturedQuad::update(EngineContext &ctx) {

}

void TexturedQuad::set_texture(const std::string &new_texture_name, EngineContext &ctx) {
    std::vector<sf::Vector2f> vertices = ctx.app->texture_atlas->get_region(new_texture_name).get_rect();
    this->quad[0].texCoords = vertices[0];
    this->quad[1].texCoords = vertices[1];
    this->quad[2].texCoords = vertices[2];
    this->quad[3].texCoords = vertices[3];
}

void TexturedQuad::set_quad(std::vector<sf::Vector2f> &vertices) {
    for (int i = 0; i < 4; i++) {
        this->quad[i].position = vertices[i];
    }
}