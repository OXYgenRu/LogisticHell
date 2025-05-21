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
    this->container_volume++;
}

void ContainerNode::add_node(std::shared_ptr<ContentNode> new_node) {
    this->content_nodes.emplace_back(new_node);
    std::weak_ptr<ContainerNode> weak_this = shared_from_this();
    new_node->parent = weak_this;
    this->container_volume++;
}

std::vector<std::shared_ptr<ContainerNode>> &ContainerNode::get_render_layer(int render_layer) {
    return this->container_nodes[render_layer];
}

int ContainerNode::get_container_volume() {
    return this->container_volume;
}

std::vector<std::shared_ptr<ContentNode>> &ContainerNode::get_content_layer() {
    return this->content_nodes;
}

int ContainerNode::get_render_layers_count() {
    return int(this->container_nodes.size());
}

void ContainerNode::set_render_layers_count(int render_layers_count) {
    this->container_nodes.resize(render_layers_count);
}

void ContainerNode::render(EngineContext &ctx, sf::RenderStates &states) {}

void ContainerNode::update(EngineContext &ctx) {}

int ContainerNode::get_node_type() const {
    return 2;
}

void ContainerNode::delete_node(std::shared_ptr<ContainerNode> node) {
    if (node == nullptr) {
        return;
    }
    auto it = std::find(this->container_nodes[node->render_priority].begin(),
                        this->container_nodes[node->render_priority].end(), node);
    if (it != this->container_nodes[node->render_priority].end()) {
        this->container_nodes[node->render_priority].erase(it);
        this->container_volume--;
    }

}

void ContainerNode::delete_node(std::shared_ptr<ContentNode> node) {
    if (node == nullptr) {
        return;
    }
    auto it = std::find(this->content_nodes.begin(),
                        this->content_nodes.end(), node);
    if (it != this->content_nodes.end()) {
        this->content_nodes.erase(it);
        this->container_volume--;
    }

}