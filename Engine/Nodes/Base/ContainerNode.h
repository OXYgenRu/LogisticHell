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

    std::vector<std::shared_ptr<ContainerNode>> &get_render_layer(int render_layer);

    int get_container_volume();

    std::vector<std::shared_ptr<ContentNode>> &get_content_layer();

    int get_render_layers_count();

    void set_render_layers_count(int render_layers_count);

    void render(EngineContext &ctx) override;

    void update(EngineContext &ctx) override;

    int get_node_type() const override;


    sf::View view_point;
private:
    int container_volume = 0;
    std::vector<std::vector<std::shared_ptr<ContainerNode>>> container_nodes;
    std::vector<std::shared_ptr<ContentNode>> content_nodes;
};


#endif //LOGISTICHELL_CONTAINERNODE_H
