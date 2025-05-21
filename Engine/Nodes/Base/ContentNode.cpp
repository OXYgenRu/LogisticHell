//
// Created by EgorRychkov on 13.04.2025.
//


#include <memory>
#include "ContentNode.h"
#include "ContainerNode.h"


std::shared_ptr<ContentNode> ContentNode::create(std::shared_ptr<ContainerNode> parent, int render_priority) {
    auto node = std::make_shared<ContentNode>(parent, render_priority);
    parent->add_node(node);
    return node;
}


void ContentNode::render(EngineContext &ctx, sf::RenderStates &states) {}

void ContentNode::update(EngineContext &ctx) {}

int ContentNode::get_node_type() const {
    return 1;
}