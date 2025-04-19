//
// Created by EgorRychkov on 13.04.2025.
//

#include "Tree.h"
#include "../Nodes/Base/ContainerNode.h"
#include "../Nodes/Base/ContentNode.h"
#include "iostream"
#include "../Nodes/Base/CameraNode.h"

void Tree::add_node(std::shared_ptr<Node> node) {
    if (this->free_tree_index == this->flatten_tree.size()) {
        this->flatten_tree.push_back(node);
        this->active_render_indices.push_back(true);
        this->active_update_indices.push_back(true);
        this->free_tree_index++;
        return;
    }
    this->flatten_tree[free_tree_index] = node;
    this->active_render_indices[free_tree_index] = true;
    this->active_update_indices[free_tree_index] = true;
    this->free_tree_index++;
}

void Tree::drop_tree() {
    this->free_tree_index = 0;
}

void Tree::traverse(std::shared_ptr<ContainerNode> &node) {
    this->add_node(std::static_pointer_cast<Node>(node));
    for (int i = 0; i < node->get_content_layer().size(); i++) {
        this->add_node(std::static_pointer_cast<Node>(node->get_content_layer()[i]));
    }
    for (int i = 0; i < node->get_render_layers_count(); i++) {
        for (auto &child: node->get_render_layer(i)) {
            this->traverse(child);
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
            if (this->flatten_tree[i]->get_node_type() == 2) {
                auto node = std::static_pointer_cast<ContainerNode>(this->flatten_tree[i]);
                render_delay += node->get_container_volume() + 1;
            } else {
                render_delay++;
            }
        } else if (render_delay) {
            if (this->flatten_tree[i]->get_node_type() == 2) {
                auto node = std::static_pointer_cast<ContainerNode>(this->flatten_tree[i]);
                render_delay += node->get_container_volume();
            }
        }
        if ((this->flatten_tree[i]->get_node_type() == 2 or this->flatten_tree[i]->get_node_type() == 3 or
             this->flatten_tree[i]->get_node_type() == 6) and !this->brunch_tracker.empty()) {
            auto node = std::static_pointer_cast<ContainerNode>(this->flatten_tree[i]);
            this->brunch_tracker.back().second += node->get_container_volume();
        }

        if (!this->brunch_tracker.empty()) {
            this->brunch_tracker.back().second--;
            if (this->brunch_tracker.back().second == 0) {
                auto node = std::static_pointer_cast<CameraNode>(this->flatten_tree[brunch_tracker.back().first]);
                node->rollback_view_point(ctx);
                this->brunch_tracker.pop_back();
            }
        }
        if (render_delay) {
            render_delay--;
            this->active_render_indices[i] = false;
        } else {
            this->active_render_indices[i] = true;
            this->flatten_tree[i]->render(ctx);
            if (this->flatten_tree[i]->get_node_type() == 6) {
                auto node = std::static_pointer_cast<CameraNode>(this->flatten_tree[i]);
                this->brunch_tracker.emplace_back(i, node->get_container_volume());
            }
        }

    }
}

void Tree::update(EngineContext &ctx) {
    int update_delay = 0;
    for (int i = 0; i < this->free_tree_index; i++) {
        if (!this->flatten_tree[i]->get_update_flag() and !update_delay) {
            if (this->flatten_tree[i]->get_node_type() == 2) {
                auto node = std::static_pointer_cast<ContainerNode>(this->flatten_tree[i]);
                update_delay += node->get_container_volume() + 1;
            } else {
                update_delay++;
            }
        } else if (update_delay) {
            if (this->flatten_tree[i]->get_node_type() == 2) {
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