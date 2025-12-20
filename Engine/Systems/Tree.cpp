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


bool compare_bypass_by_priority(const BypassUnit &a, const BypassUnit &b) {
    return a.global_render_priority < b.global_render_priority;
}


void Tree::add_node(const std::shared_ptr<Node> &node, EngineContext &ctx, const sf::Transform &transform,
                    int render_priority) {
    node->set_cached_recursive_transform(transform);
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
        int new_render_priority = child->get_render_priority();
        if (child->get_priority_dependency()) {
            new_render_priority += render_priority;
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

void
Tree::bypass_collection(const std::shared_ptr<Node> &node, int indent,
                        std::vector<BypassUnit> &bypass, std::vector<std::string> &history, int render_priority) {
    bypass.emplace_back(node, render_priority, history);
    for (auto &child: node->get_container()) {
        history.emplace_back(child->get_node_id());
        int new_render_priority = child->get_render_priority();
        if (child->get_priority_dependency()) {
            new_render_priority += render_priority;
        }
        bypass_collection(child, indent + 1, bypass, history, new_render_priority);
        history.pop_back();
    }
}


std::vector<BypassUnit> Tree::get_tree_bypass(EngineContext &ctx) {
    std::vector<BypassUnit> bypass;
    std::vector<std::string> history;
    bypass_collection(std::static_pointer_cast<Node>(ctx.app->scene_system->currentScene), 0, bypass, history, 0);
    return bypass;
}

std::vector<BypassUnit> Tree::get_sorted_tree_bypass(EngineContext &ctx) {
    std::vector<BypassUnit> sorted_bypass = get_tree_bypass(ctx);
    std::sort(sorted_bypass.begin(), sorted_bypass.end(), compare_bypass_by_priority);
    return sorted_bypass;
}