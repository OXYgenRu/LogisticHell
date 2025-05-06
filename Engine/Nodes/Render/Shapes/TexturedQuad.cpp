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
    ctx.app->window->draw(quad, &texture);
}

void TexturedQuad::update(EngineContext &ctx) {

}

void TexturedQuad::set_texture(const std::string &path) {
    this->texture.loadFromFile(path);
    this->quad[0].texCoords = sf::Vector2f(0.f, this->texture.getSize().y);
    this->quad[1].texCoords = sf::Vector2f(0.f, 0.f);
    this->quad[2].texCoords = sf::Vector2f(this->texture.getSize().x,
                                           0.f);
    this->quad[3].texCoords = sf::Vector2f(this->texture.getSize().x, this->texture.getSize().y);
}

void TexturedQuad::set_quad(std::vector<sf::Vector2f> &vertices) {
    for (int i = 0; i < 4; i++) {
        this->quad[i].position = vertices[i];
    }
}