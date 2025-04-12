//
// Created by EgorRychkov on 12.04.2025.
//
#include "Node.h"

Node::Node(std::shared_ptr<ContainerNode> &parent) {
    this->parent = parent;
}

//void Node::add_node(const std::shared_ptr<Node> &new_node) {
//    this->children.emplace_back(new_node);
//}