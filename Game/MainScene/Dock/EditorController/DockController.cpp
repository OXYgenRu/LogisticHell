//
// Created by EgorRychkov on 02.05.2025.
//

#include "DockController.h"
#include "../../../../Engine/Nodes/Base/Node.h"
#include "../Dock.h"
#include "iostream"


std::shared_ptr<DockController>
DockController::create(const std::shared_ptr<Node> &parent, const std::shared_ptr<Dock> &dock,
                       const std::string &node_id, int render_priority) {
    auto node = std::make_shared<DockController>(parent, node_id, render_priority);
    node->dock = dock;
    parent->add_node(node);
    return node;
}


void DockController::on_key_release(sf::Event &event, EngineContext &ctx) {
    this->dock.lock()->editor_controller->on_key_release(event, ctx);
}
