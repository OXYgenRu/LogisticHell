//
// Created by EgorRychkov on 12.04.2025.
//



#ifndef LOGISTICHELL_CONTAINERNODE_H
#define LOGISTICHELL_CONTAINERNODE_H


#include "Node.h"

class ContainerNode : public Node, public std::enable_shared_from_this<ContainerNode> {
public:
    explicit ContainerNode(std::shared_ptr<ContainerNode> &parent)
            : Node(parent) {}

    void add_node(std::shared_ptr<Node> &new_node);
};


#endif //LOGISTICHELL_CONTAINERNODE_H
