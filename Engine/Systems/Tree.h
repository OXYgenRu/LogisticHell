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

struct BypassUnit {
    std::shared_ptr<Node> node;
    int global_render_priority;
    std::vector<std::string> history;

    BypassUnit(const std::shared_ptr<Node> &node, int global_render_priority, std::vector<std::string> &history) {
        this->node = node;
        this->global_render_priority = global_render_priority;
        this->history = history;
    }
};

class Tree {
private:
    void
    bypass_collection(const std::shared_ptr<Node> &node, int indent, std::vector<BypassUnit> &bypass,
                      std::vector<std::string> &history, int render_priority);

    std::vector<Leaf> flatten_tree;
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

    std::vector<BypassUnit> get_tree_bypass(EngineContext &ctx);

    std::vector<BypassUnit> get_sorted_tree_bypass(EngineContext &ctx);

    void drop_tree();

    std::vector<Leaf> &get_tree();
};


#endif //LOGISTICHELL_TREE_H
