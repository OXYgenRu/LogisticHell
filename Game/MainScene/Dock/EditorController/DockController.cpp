//
// Created by EgorRychkov on 02.05.2025.
//

#include "DockController.h"
#include "../../../../Engine/Nodes/Base/ContainerNode.h"
#include "../Dock.h"
#include "iostream"


std::shared_ptr<DockController>
DockController::create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<Dock> dock, int render_priority) {
    auto node = std::make_shared<DockController>(parent, render_priority);
    node->dock = dock;
    parent->add_node(node);
    return node;
}


void DockController::on_key_release(sf::Event &event, EngineContext &ctx) {
    this->dock.lock()->editor_controller->on_key_release(event, ctx);
}
