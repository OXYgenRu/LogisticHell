//
// Created by EgorRychkov on 13.04.2025.
//

#include "Tree.h"
#include "../Nodes/Base/ContainerNode.h"
#include "../Nodes/Base/ContentNode.h"
#include "iostream"

void Tree::add_node(std::shared_ptr<Node> node) {
    if (this->free_tree_index == this->flatten_tree.size()) {
        this->flatten_tree.push_back(node);
        this->free_tree_index++;
        return;
    }
    this->flatten_tree[free_tree_index] = node;
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
        if (render_delay) {
            render_delay--;
        } else {
            this->flatten_tree[i]->render(ctx);
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
        } else {
            this->flatten_tree[i]->update(ctx);
        }
    }
}