//
// Created by EgorRychkov on 22.04.2025.
//

#include "TestCollider.h"
#include "../../../Engine/Nodes/Base/ContainerNode.h"

std::shared_ptr<TestCollider> TestCollider::create(std::shared_ptr<ContainerNode> parent, int render_priority) {
    auto node = std::make_shared<TestCollider>(parent, render_priority);
    parent->add_node(node);
    return node;
}
//
//void TestCollider::handle_mouse_press(sf::Event &event, EngineContext &ctx) {
//    std::cout << "Click!" << '\n';
//}