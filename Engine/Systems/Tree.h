//
// Created by EgorRychkov on 13.04.2025.
//


#ifndef LOGISTICHELL_TREE_H
#define LOGISTICHELL_TREE_H

#include "../Nodes/Base/Node.h"
#include "../Nodes/Base/ContainerNode.h"

class Tree {
private:
    int free_tree_index = 0;
    std::vector<std::shared_ptr<Node>> flatten_tree;
    std::vector<bool> active_render_indices, active_update_indices;
    std::vector<std::pair<int, int>> brunch_tracker;
public:
    void add_node(std::shared_ptr<Node> node);

    void drop_tree();

    void traverse(std::shared_ptr<ContainerNode> &node);

    std::vector<std::shared_ptr<Node>> &get_tree();

    void render(EngineContext &ctx);

    void update(EngineContext &ctx);

    std::vector<bool> &get_active_render_indices();

    std::vector<bool> &get_active_update_indices();

    [[nodiscard]] int get_free_tree_index() const;

    std::vector<std::shared_ptr<Node>> &get_flatten_tree();
};


#endif //LOGISTICHELL_TREE_H
