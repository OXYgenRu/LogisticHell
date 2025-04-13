//
// Created by EgorRychkov on 13.04.2025.
//

#include "ContentNode.h"

#include <memory>
#include "ContainerNode.h"


std::shared_ptr<ContentNode> ContentNode::create(std::shared_ptr<ContainerNode> parent) {
    auto node = std::make_shared<ContentNode>(parent);
    parent->add_node(node);
    return node;
}

void ContentNode::get_tree(EngineContext &ctx) {

}

void ContentNode::render() {}

void ContentNode::update(float dt) {}

bool ContentNode::is_leaf() const {
    return true;
}