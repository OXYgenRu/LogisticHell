//
// Created by EgorRychkov on 13.04.2025.
//


#ifndef LOGISTICHELL_TREE_H
#define LOGISTICHELL_TREE_H

#include "../Nodes/Base/Node.h"

struct Leaf {
    std::shared_ptr<Node> node;
    bool is_render_active;
    bool is_update_active;
    sf::Transform transform;
    int global_render_priority;

    Leaf() {
        node = nullptr;
        is_render_active = false;
        is_update_active = false;
        global_render_priority = 0;
    }

    Leaf(const std::shared_ptr<Node> &node, bool is_render_active, bool is_update_active,
         const sf::Transform &transform, int global_render_priority) {
        this->node = node;
        this->is_render_active = is_render_active;
        this->is_update_active = is_update_active;
        this->transform = transform;
        this->global_render_priority = global_render_priority;
    }

};

class Tree {
private:
    std::vector<Leaf> flatten_tree;
    std::vector<std::pair<int, int>> brunch_tracker;
    sf::RenderStates states;
    int free_tree_index = 0;
public:
    void add_node(const std::shared_ptr<Node> &node, EngineContext &ctx, const sf::Transform &transform,
                  int render_priority);

    void traverse(std::shared_ptr<Node> &node, EngineContext &ctx, sf::Transform transform, int render_priority);

    void prepare_tree();

    void render(EngineContext &ctx);

    void update(EngineContext &ctx);

    [[nodiscard]] int get_free_tree_index() const;

    std::vector<Leaf> &get_flatten_tree();

    void print_tree(std::shared_ptr<Node> &node, EngineContext &ctx);

    void traverse_print(std::shared_ptr<Node> &node, const std::string &indent = "");

    void drop_tree();

    std::vector<Leaf> &get_tree();
};


#endif //LOGISTICHELL_TREE_H
