//
// Created by EgorRychkov on 12.04.2025.
//
#include "SFML/Graphics.hpp"
#include "../../EngineContext.h"
#include <memory>

#ifndef LOGISTICHELL_NODE_H
#define LOGISTICHELL_NODE_H

class ContainerNode;

class Node {
public:
    virtual ~Node() = default;

    explicit Node(std::shared_ptr<ContainerNode> &parent);

    virtual void get_tree(EngineContext ctx) = 0;

//    void add_node(const std::shared_ptr<Node> &new_node);

    virtual void render() = 0;

    virtual void update(float dt) = 0;

    [[nodiscard]] virtual bool isLeaf() const = 0;

    std::vector<std::shared_ptr<Node>> children;
    std::weak_ptr<ContainerNode> parent;

};


#endif //LOGISTICHELL_NODE_H
