//
// Created by EgorRychkov on 27.04.2025.
//

#include <iostream>
#include "TestController.h"
#include "../../../Engine/Nodes/Base/ContainerNode.h"

std::shared_ptr<TestController>
TestController::create(std::shared_ptr<ContainerNode> parent, b2BodyId body, int render_priority) {
    auto node = std::make_shared<TestController>(parent, render_priority);
    node->body = body;
    parent->add_node(node);
    return node;
}

void TestController::update(EngineContext &ctx) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        b2Body_ApplyForceToCenter(this->body, b2Vec2({0, 1000}), true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        b2Body_ApplyForceToCenter(this->body, b2Vec2({0, -1000}), true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        b2Body_ApplyForceToCenter(this->body, b2Vec2({1000, 0}), true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        b2Body_ApplyForceToCenter(this->body, b2Vec2({-1000, 0}), true);
    }
}