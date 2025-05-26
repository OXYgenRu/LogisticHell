//
// Created by EgorRychkov on 24.04.2025.
//

#include "Sprite.h"
#include "../../Base/Node.h"
#include "../../../Application.h"

std::shared_ptr<Sprite> Sprite::create(const std::shared_ptr<Node> &parent, int render_priority) {
    auto node = std::make_shared<Sprite>(parent, render_priority);
    parent->add_node(node);
    return node;
}

void Sprite::render(EngineContext &ctx, sf::RenderStates &states) {
    ctx.app->window->draw(this->sprite);
}

void Sprite::update(EngineContext &ctx) {

}

int Sprite::get_node_type() const {
    return 10;
}