//
// Created by EgorRychkov on 12.04.2025.
//
#include "Node.h"


std::shared_ptr<Node> Node::create(const std::shared_ptr<Node> &parent, int render_priority) {
    auto node = std::make_shared<Node>(parent, render_priority);
    parent->add_node(node);
    return node;
}

Node::Node(const std::shared_ptr<Node> &parent, int render_priority) {
    this->parent = parent;
    this->render_priority = render_priority;
    this->container_volume = 0;
    this->priority_as_relative = true;
}

void Node::set_render_flag(bool flag) {
    this->render_enabled = flag;
}

void Node::set_update_flag(bool flag) {
    this->update_enabled = flag;
}

void Node::set_priority_relativity(bool is_priority_relative) {
    this->priority_as_relative = is_priority_relative;
}

int Node::get_render_priority() const {
    return this->render_priority;
}

void Node::set_render_priority(int new_render_priority) {
    this->render_priority = new_render_priority;
}

bool Node::get_priority_dependency() const {
    return this->priority_as_relative;
}

bool Node::get_render_flag() const {
    return this->render_enabled;
}

bool Node::get_update_flag() const {
    return this->update_enabled;
}

sf::Transformable &Node::get_transformable() {
    return this->transform;
}

void Node::set_position(const sf::Vector2f &position) {
    transform.setPosition(position);
}

const sf::Vector2f &Node::get_origin() {
    return transform.getOrigin();
}

void Node::set_origin(const sf::Vector2f &position) {
    this->transform.setOrigin(position);
}

void Node::set_scale(float new_scale) {
    this->transform.setScale(new_scale, new_scale);
}

const sf::Vector2f &Node::get_position() {
    return transform.getPosition();
}

void Node::set_rotation(float angle) {
    transform.setRotation(angle);
}

float Node::get_rotation() {
    return transform.getRotation();
}


std::string Node::get_node_type_str(std::shared_ptr<Node> node) {
    if (node->get_node_type() == 1) {
        return "ContentNode";
    }
    if (node->get_node_type() == 2) {
        return "ContainerNode";
    }
    if (node->get_node_type() == 3) {
        return "TestScene";
    }
    if (node->get_node_type() == 4) {
        return "Polygon";
    }
    if (node->get_node_type() == 5) {
        return "Controller";
    }
    if (node->get_node_type() == 6) {
        return "Camera";
    }
    if (node->get_node_type() == 7) {
        return "CameraController";
    }
    if (node->get_node_type() == 8) {
        return "Text";
    }
    if (node->get_node_type() == 9) {
        return "UICollider";
    }
    if (node->get_node_type() == 10) {
        return "Sprite";
    }
    if (node->get_node_type() == 11) {
        return "RigidBody";
    }
    return "Not found";
}


void Node::add_node(const std::shared_ptr<Node> &new_node) {
    this->container.emplace_back(new_node);
    std::weak_ptr<Node> weak_this = shared_from_this();
    new_node->parent = weak_this;
    this->container_volume++;
}

void Node::delete_node(const std::shared_ptr<Node> &node) {
    if (node == nullptr) {
        return;
    }
    auto it = std::find(this->container.begin(),
                        this->container.end(), node);
    if (it != this->container.end()) {
        this->container.erase(it);
        this->container_volume--;
    }
}

int Node::get_container_volume() const {
    return this->container_volume;
}

int Node::get_node_type() const {
    return 1;
}

std::vector<std::shared_ptr<Node>> &Node::get_container() {
    return this->container;
}

void Node::render(EngineContext &ctx, sf::RenderStates &states) {

}

void Node::update(EngineContext &ctx) {

}

void Node::clear_container() {
    this->container.clear();
    this->container_volume = 0;
}