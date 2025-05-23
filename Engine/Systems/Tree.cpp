//
// Created by EgorRychkov on 13.04.2025.
//

#include "Tree.h"
#include "../Nodes/Base/ContainerNode.h"
#include "../Nodes/Base/ContentNode.h"
#include "iostream"
#include "../Nodes/Base/CameraNode.h"
#include "../Application.h"

void Tree::add_node(std::shared_ptr<Node> node, EngineContext &ctx, sf::Transform transform) {
    if (this->free_tree_index == this->flatten_tree.size()) {
        this->flatten_tree.push_back(node);
        this->active_render_indices.push_back(true);
        this->active_update_indices.push_back(true);
        this->transform_tracker.push_back(transform);
        this->free_tree_index++;
        return;
    }
    this->flatten_tree[free_tree_index] = node;
    this->active_render_indices[free_tree_index] = true;
    this->active_update_indices[free_tree_index] = true;
    this->transform_tracker[free_tree_index] = transform;
    this->free_tree_index++;
}

void Tree::drop_tree() {
    this->free_tree_index = 0;
}

void Tree::traverse(std::shared_ptr<ContainerNode> &node, EngineContext &ctx, sf::Transform transform) {
    this->add_node(std::static_pointer_cast<Node>(node), ctx, transform);
    for (int i = 0; i < node->get_content_layer().size(); i++) {
        this->add_node(std::static_pointer_cast<Node>(node->get_content_layer()[i]), ctx,
                       transform * node->get_content_layer()[i]->get_transformable().getTransform());
    }
    for (int i = 0; i < node->get_render_layers_count(); i++) {
        for (auto &child: node->get_render_layer(i)) {
            if (child->get_node_type() == 6) {
                this->traverse(child, ctx, transform * child->get_transformable().getInverseTransform());
            } else {
                this->traverse(child, ctx, transform * child->get_transformable().getTransform());
            }

        }
    }

}

std::vector<std::shared_ptr<Node>> &Tree::get_tree() {
    return this->flatten_tree;
}

void Tree::render(EngineContext &ctx) {
    int render_delay = 0;
    for (int i = 0; i < this->free_tree_index; i++) {
        if (!this->flatten_tree[i]->get_render_flag() and !render_delay) {
            if (this->flatten_tree[i]->get_node_type() == 2 or this->flatten_tree[i]->get_node_type() == 6) {
                auto node = std::static_pointer_cast<ContainerNode>(this->flatten_tree[i]);
                render_delay += node->get_container_volume() + 1;
            } else {
                render_delay++;
            }
        } else if (render_delay) {
            if (this->flatten_tree[i]->get_node_type() == 2 or this->flatten_tree[i]->get_node_type() == 6) {
                auto node = std::static_pointer_cast<ContainerNode>(this->flatten_tree[i]);
                render_delay += node->get_container_volume();
            }
        }
        if (render_delay) {
            render_delay--;
            this->active_render_indices[i] = false;
        } else {
            this->active_render_indices[i] = true;
            states.transform = this->transform_tracker[i];
            this->flatten_tree[i]->render(ctx, states);
        }
    }
}

void Tree::update(EngineContext &ctx) {
    int update_delay = 0;
    for (int i = 0; i < this->free_tree_index; i++) {
        if (!this->flatten_tree[i]->get_update_flag() and !update_delay) {
            if (this->flatten_tree[i]->get_node_type() == 2 or this->flatten_tree[i]->get_node_type() == 6) {
                auto node = std::static_pointer_cast<ContainerNode>(this->flatten_tree[i]);
                update_delay += node->get_container_volume() + 1;
            } else {
                update_delay++;
            }
        } else if (update_delay) {
            if (this->flatten_tree[i]->get_node_type() == 2 or this->flatten_tree[i]->get_node_type() == 6) {
                auto node = std::static_pointer_cast<ContainerNode>(this->flatten_tree[i]);
                update_delay += node->get_container_volume();
            }
        }
        if (update_delay) {
            update_delay--;
            this->active_update_indices[i] = false;
        } else {
            this->active_update_indices[i] = true;
            this->flatten_tree[i]->update(ctx);
        }
    }
}

std::vector<bool> &Tree::get_active_render_indices() {
    return this->active_render_indices;
}

std::vector<bool> &Tree::get_active_update_indices() {
    return this->active_update_indices;
}

int Tree::get_free_tree_index() const {
    return this->free_tree_index;
}

std::vector<std::shared_ptr<Node>> &Tree::get_flatten_tree() {
    return this->flatten_tree;
}

void Tree::print_tree(std::shared_ptr<ContainerNode> &node, const std::string &indent) {
    std::cout << indent << Node::get_node_type_str(node) << '\n';
    for (int i = 0; i < node->get_content_layer().size(); i++) {
        std::cout << indent << "-" << Node::get_node_type_str(node->get_content_layer()[i]) << '\n';
    }
    for (int i = 0; i < node->get_render_layers_count(); i++) {
        for (auto &child: node->get_render_layer(i)) {
            this->print_tree(child, indent + "-");
        }
    }

}


std::vector<sf::Transform> &Tree::get_transform_tracker() {
    return this->transform_tracker;
}