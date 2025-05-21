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

sf::Transformable &Node::get_transformable() {
    return this->transform;
}

void Node::set_position(const sf::Vector2f &position) {
    transform.setPosition(position);
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
    return "Not found";
}