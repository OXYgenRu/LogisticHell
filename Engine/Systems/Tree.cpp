//
// Created by EgorRychkov on 13.04.2025.
//

#include "Tree.h"
#include "iostream"
#include "../Nodes/Base/CameraNode.h"
#include "../Application.h"


bool compare_by_priority(const Leaf &a, const Leaf &b) {
    return a.global_render_priority < b.global_render_priority;
}


void Tree::add_node(const std::shared_ptr<Node> &node, EngineContext &ctx, const sf::Transform &transform,
                    int render_priority) {
    if (this->free_tree_index == this->flatten_tree.size()) {
        this->flatten_tree.emplace_back(node, node->get_render_flag(), node->get_update_flag(), transform,
                                        render_priority);
        this->free_tree_index++;
        return;
    }
    this->flatten_tree[free_tree_index].transform = transform;
    this->flatten_tree[free_tree_index].node = node;
    this->flatten_tree[free_tree_index].global_render_priority = render_priority;
    this->flatten_tree[free_tree_index].is_update_active = node->get_update_flag();
    this->flatten_tree[free_tree_index].is_render_active = node->get_render_flag();
    this->free_tree_index++;
}

void Tree::drop_tree() {
    this->free_tree_index = 0;
}

void Tree::traverse(std::shared_ptr<Node> &node, EngineContext &ctx, sf::Transform transform, int render_priority) {
    this->add_node(node, ctx, transform, render_priority);
    for (auto &child: node->get_container()) {
        int new_render_priority = render_priority;
        if (child->get_priority_dependency()) {
            new_render_priority += child->get_render_priority();
        }
        if (child->get_node_type() == 6) {
            this->traverse(child, ctx, transform * child->get_transformable().getInverseTransform(),
                           new_render_priority);
        } else {
            this->traverse(child, ctx, transform * child->get_transformable().getTransform(), new_render_priority);
        }
    }
}

std::vector<Leaf> &Tree::get_tree() {
    return this->flatten_tree;
}

void Tree::prepare_tree() {
    int render_delay = 0;
    int update_delay = 0;
    for (int i = 0; i < this->free_tree_index; i++) {
        if (!this->flatten_tree[i].is_render_active and !render_delay) {
            render_delay += this->flatten_tree[i].node->get_container_volume() + 1;
        } else if (render_delay) {
            render_delay += this->flatten_tree[i].node->get_container_volume();
        }
        if (!this->flatten_tree[i].is_update_active and !update_delay) {
            update_delay += this->flatten_tree[i].node->get_container_volume() + 1;
        } else if (update_delay) {
            update_delay += this->flatten_tree[i].node->get_container_volume();
        }
        if (render_delay) {
            render_delay--;
            this->flatten_tree[i].is_render_active = false;
        } else {
            this->flatten_tree[i].is_render_active = true;
        }
        if (update_delay) {
            update_delay--;
            this->flatten_tree[i].is_update_active = false;
        } else {
            this->flatten_tree[i].is_update_active = true;
        }
    }
    for (int i = this->free_tree_index; i < this->flatten_tree.size(); i++) {
        this->flatten_tree[i].node = nullptr;
    }
    std::sort(this->flatten_tree.begin(), this->flatten_tree.begin() + this->free_tree_index, compare_by_priority);
}

void Tree::render(EngineContext &ctx) {
    for (int i = 0; i < this->free_tree_index; i++) {
        if (!this->flatten_tree[i].is_render_active) {
            continue;
        }
        states.transform = this->flatten_tree[i].transform;
        this->flatten_tree[i].node->render(ctx, states);
    }
    ctx.app->batch->flush(ctx);
}

void Tree::update(EngineContext &ctx) {
    for (int i = 0; i < this->free_tree_index; i++) {
        if (!this->flatten_tree[i].is_update_active) {
            continue;
        }
        this->flatten_tree[i].node->update(ctx);
    }
}

int Tree::get_free_tree_index() const {
    return this->free_tree_index;
}

std::vector<Leaf> &Tree::get_flatten_tree() {
    return this->flatten_tree;
}


void Tree::print_tree(std::shared_ptr<Node> &node, EngineContext &ctx) {
    sf::Transform scene_transform;
    scene_transform.translate(ctx.app->get_window_size().x / 2, ctx.app->get_window_size().y / 2);
    this->traverse_print(node, "");
    traverse(node, ctx, scene_transform, 0);
    this->prepare_tree();
    for (int i = 0; i < free_tree_index; i++) {
        std::cout << Node::get_node_type_str(flatten_tree[i].node) << ' ' << flatten_tree[i].global_render_priority
                  << '\n';
    }
}

void Tree::traverse_print(std::shared_ptr<Node> &node, const std::string &indent) {
    std::cout << indent << Node::get_node_type_str(node) << '\n';
    for (auto &child: node->get_container()) {
        this->traverse_print(child, indent + "-");
    }
}