//
// Created by EgorRychkov on 17.04.2025.
//

#ifndef LOGISTICHELL_CAMERANODE_H
#define LOGISTICHELL_CAMERANODE_H


#include <SFML/Graphics/View.hpp>
#include "../Control/CameraController.h"
#include "../Base/Node.h"

class CameraNode : public Node {
public:
    static std::shared_ptr<CameraNode>
    create(const std::shared_ptr<Node> &parent, EngineContext &ctx, const std::string &node_id,
           int render_priority = 0);

    explicit CameraNode(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0)
            : Node(parent, node_id, render_priority) {}


    void set_zoom(float zoom);

    void set_camera_target(sf::Vector2f camera_target);

    void set_locked(bool is_locked);

    float get_zoom();

    int get_node_type() const override;

    const sf::Transform &get_transform();

    std::shared_ptr<CameraController> camera_controller;
    float zoom;
private:
    bool locked;
};


#endif //LOGISTICHELL_CAMERANODE_H
