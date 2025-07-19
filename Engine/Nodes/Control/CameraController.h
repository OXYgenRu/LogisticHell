//
// Created by EgorRychkov on 19.04.2025.
//

#ifndef LOGISTICHELL_CAMERACONTROLLER_H
#define LOGISTICHELL_CAMERACONTROLLER_H

#include "Controller.h"

class CameraNode;

class CameraController : public Controller {
public:
    static std::shared_ptr<CameraController>
    create(const std::shared_ptr<Node> &parent, const std::shared_ptr<CameraNode> &camera, const std::string &node_id,
           int render_priority = 0);

    explicit CameraController(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0)
            : Controller(parent, node_id,
                         render_priority) {}

    void render(EngineContext &ctx, sf::RenderStates &states) override;

    void update(EngineContext &ctx) override;

    int get_node_type() const override;

    void on_mouse_press(sf::Event &event, EngineContext &ctx) override;

    void on_mouse_release(sf::Event &event, EngineContext &ctx) override;

    void on_mouse_moved(sf::Event &event, EngineContext &ctx) override;

    void on_mouse_wheel_scrolled(sf::Event &event, EngineContext &ctx) override;

    bool wheel_pressed = false;

    sf::Vector2f start_mouse_pos;

    std::weak_ptr<CameraNode> camera;
};


#endif //LOGISTICHELL_CAMERACONTROLLER_H
