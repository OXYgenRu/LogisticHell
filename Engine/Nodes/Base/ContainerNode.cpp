//
// Created by EgorRychkov on 12.04.2025.
//

#include "ContainerNode.h"

void ContainerNode::add_node(std::shared_ptr<Node> &new_node) {
    this->children.emplace_back(new_node);
    std::weak_ptr<ContainerNode> weak_this = shared_from_this();
    new_node->parent = weak_this;
}