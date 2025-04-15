//
// Created by EgorRychkov on 12.04.2025.
//



#ifndef LOGISTICHELL_CONTAINERNODE_H
#define LOGISTICHELL_CONTAINERNODE_H


#include "Node.h"

class ContentNode;

class ContainerNode : public Node, public std::enable_shared_from_this<ContainerNode> {
public:
    static std::shared_ptr<ContainerNode>
    create(std::shared_ptr<ContainerNode> parent, int render_priority = 0, int render_priority_layers = 10);


    explicit ContainerNode(std::shared_ptr<ContainerNode> parent, int render_priority = 0)
            : Node(parent, render_priority) {}

    void add_node(std::shared_ptr<ContainerNode> new_node);

    void add_node(std::shared_ptr<ContentNode> new_node);

    void render() override;

    void update(float dt) override;

    int get_node_type() const override;

    std::vector<std::vector<std::shared_ptr<ContainerNode>>> container_nodes;
    std::vector<std::shared_ptr<ContentNode>> content_nodes;

    sf::View view_point;

};


#endif //LOGISTICHELL_CONTAINERNODE_H
