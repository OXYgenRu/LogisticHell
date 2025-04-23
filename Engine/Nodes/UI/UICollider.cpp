//
// Created by EgorRychkov on 20.04.2025.
//

#include "UICollider.h"
#include "../Base/ContainerNode.h"

std::shared_ptr<UICollider> UICollider::create(std::shared_ptr<ContainerNode> parent, int render_priority) {
    auto node = std::make_shared<UICollider>(parent, render_priority);
    parent->add_node(node);
    return node;
}

void UICollider::render(EngineContext &ctx) {

}

void UICollider::update(EngineContext &ctx) {

}

int UICollider::get_node_type() const {
    return 9;
}

void UICollider::on_mouse_press(sf::Event &event, EngineContext &ctx) {

}

void UICollider::on_mouse_release(sf::Event &event, EngineContext &ctx) {

}

void UICollider::on_mouse_moved(sf::Event &event, EngineContext &ctx) {

}