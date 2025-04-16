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

    explicit Node(std::shared_ptr<ContainerNode> parent, int render_priority = 0);

    virtual void render(EngineContext &ctx) = 0;

    virtual void update(float dt) = 0;


    [[nodiscard]] virtual int get_node_type() const = 0;

    void set_render_flag(bool flag);

    void set_update_flag(bool flag);

    bool get_render_flag();

    bool get_update_flag();

    std::weak_ptr<ContainerNode> parent;
    int render_priority = 0;
private:
    bool render_enabled = true;
    bool update_enabled = true;
};


#endif //LOGISTICHELL_NODE_H
