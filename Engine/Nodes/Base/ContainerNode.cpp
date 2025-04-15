//
// Created by EgorRychkov on 12.04.2025.
//

#include "ContainerNode.h"
#include "ContentNode.h"

std::shared_ptr<ContainerNode>
ContainerNode::create(std::shared_ptr<ContainerNode> parent, int render_priority, int render_priority_layers) {
    auto node = std::make_shared<ContainerNode>(parent, render_priority);
    node->container_nodes.resize(render_priority_layers + 1);
    parent->add_node(node);
    return node;
}

void ContainerNode::add_node(std::shared_ptr<ContainerNode> new_node) {
    this->container_nodes[new_node->render_priority].emplace_back(new_node);
    std::weak_ptr<ContainerNode> weak_this = shared_from_this();
    new_node->parent = weak_this;
}

void ContainerNode::add_node(std::shared_ptr<ContentNode> new_node) {
    this->content_nodes.emplace_back(new_node);
    std::weak_ptr<ContainerNode> weak_this = shared_from_this();
    new_node->parent = weak_this;
}



void ContainerNode::render() {}

void ContainerNode::update(float dt) {}

int ContainerNode::get_node_type() const {
    return 2;
}