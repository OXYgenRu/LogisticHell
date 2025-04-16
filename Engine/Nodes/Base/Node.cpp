//
// Created by EgorRychkov on 12.04.2025.
//
#include "Node.h"

Node::Node(std::shared_ptr<ContainerNode> parent, int render_priority) {
    this->parent = parent;
    this->render_priority = render_priority;
}

//void Node::add_node(const std::shared_ptr<Node> &new_node) {
//    this->children.emplace_back(new_node);
//}

void Node::set_render_flag(bool flag) {
    this->render_enabled = flag;
}

void Node::set_update_flag(bool flag) {
    this->update_enabled = flag;
}

bool Node::get_render_flag() {
    return this->render_enabled;
}

bool Node::get_update_flag() {
    return this->update_enabled;
}