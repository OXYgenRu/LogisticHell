//
// Created by EgorRychkov on 24.04.2025.
//

#include "Sprite.h"
#include "../../Base/ContainerNode.h"
#include "../../../Application.h"

std::shared_ptr<Sprite> Sprite::create(std::shared_ptr<ContainerNode> parent, int render_priority) {
    auto node = std::make_shared<Sprite>(parent, render_priority);
    parent->add_node(node);
    return node;
}

void Sprite::render(EngineContext &ctx) {
    ctx.app->window->draw(this->sprite);
}

void Sprite::update(EngineContext &ctx) {

}

int Sprite::get_node_type() const {
    return 10;
}