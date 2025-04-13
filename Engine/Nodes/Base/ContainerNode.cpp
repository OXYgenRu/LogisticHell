//
// Created by EgorRychkov on 12.04.2025.
//

#include "ContainerNode.h"


std::shared_ptr<ContainerNode> ContainerNode::create(std::shared_ptr<ContainerNode> parent) {
    auto node = std::make_shared<ContainerNode>(parent);
    parent->add_node(node);
    return node;
}

void ContainerNode::add_node(std::shared_ptr<Node> new_node) {
    this->children.emplace_back(new_node);
    std::weak_ptr<ContainerNode> weak_this = shared_from_this();
    new_node->parent = weak_this;
}

void ContainerNode::get_tree(EngineContext &ctx) {

}

void ContainerNode::render() {}

void ContainerNode::update(float dt) {}

bool ContainerNode::is_leaf() const {
    return false;
}