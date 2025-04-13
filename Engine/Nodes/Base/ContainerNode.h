//
// Created by EgorRychkov on 12.04.2025.
//



#ifndef LOGISTICHELL_CONTAINERNODE_H
#define LOGISTICHELL_CONTAINERNODE_H


#include "Node.h"

class ContainerNode : public Node, public std::enable_shared_from_this<ContainerNode> {
public:
    static std::shared_ptr<ContainerNode> create(std::shared_ptr<ContainerNode> parent);


    explicit ContainerNode(std::shared_ptr<ContainerNode> parent)
            : Node(parent) {}

    void add_node(std::shared_ptr<Node> new_node);

    void get_tree(EngineContext &ctx) override;

    void render() override;

    void update(float dt) override;

    bool is_leaf() const override;
};


#endif //LOGISTICHELL_CONTAINERNODE_H
