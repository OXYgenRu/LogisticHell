//
// Created by EgorRychkov on 13.04.2025.
//

#include "Tree.h"
#include "../Nodes/Base/ContainerNode.h"
#include "../Nodes/Base/ContentNode.h"

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
    for (int i = 0; i < node->content_nodes.size(); i++) {
        this->add_node(std::static_pointer_cast<Node>(node->content_nodes[i]));
    }
    for (int i = 0; i < node->container_nodes.size(); i++) {
        for (auto &child: node->container_nodes[i]) {
            this->traverse(child);
        }
    }

}

std::vector<std::shared_ptr<Node>> &Tree::get_tree() {
    return this->flatten_tree;
}