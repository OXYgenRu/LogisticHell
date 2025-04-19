//
// Created by EgorRychkov on 17.04.2025.
//

#ifndef LOGISTICHELL_CAMERANODE_H
#define LOGISTICHELL_CAMERANODE_H


#include <SFML/Graphics/View.hpp>
#include "ContainerNode.h"
#include "../Control/CameraController.h"

class CameraNode : public ContainerNode {
public:
    static std::shared_ptr<CameraNode>
    create(std::shared_ptr<ContainerNode> parent, EngineContext &ctx, int render_priority = 0,
           int render_priority_layers = 10);

    explicit CameraNode(std::shared_ptr<ContainerNode> parent, int render_priority = 0)
            : ContainerNode(parent, render_priority) {}


    void set_zoom(float zoom);

    void set_camera_target(sf::Vector2f camera_target);

    sf::View view_point;
    sf::Vector2f original_size;

    int get_node_type() const override;

    float zoom;

    void rollback_view_point(EngineContext &ctx);

    void render(EngineContext &ctx) override;

    std::shared_ptr<CameraController> camera_controller;

};


#endif //LOGISTICHELL_CAMERANODE_H
