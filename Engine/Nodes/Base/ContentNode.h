//
// Created by EgorRychkov on 13.04.2025.
//
#include "Node.h"

#ifndef LOGISTICHELL_CONTENTNODE_H
#define LOGISTICHELL_CONTENTNODE_H


class ContentNode : public Node, public std::enable_shared_from_this<ContentNode> {
public:
    static std::shared_ptr<ContentNode> create(std::shared_ptr<ContainerNode> parent, int render_priority = 0);

    explicit ContentNode(std::shared_ptr<ContainerNode> parent, int render_priority = 0) : Node(parent,
                                                                                                render_priority) {}


    void render() override;

    void update(float dt) override;

    int get_node_type() const override;
};


#endif //LOGISTICHELL_CONTENTNODE_H
