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