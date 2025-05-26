//
// Created by EgorRychkov on 16.04.2025.
//

#ifndef LOGISTICHELL_CONTROLLER_H
#define LOGISTICHELL_CONTROLLER_H

#include "../Base/Node.h"
#include "SFML/Graphics.hpp"

class Controller : public Node {
public:
    static std::shared_ptr<Controller> create(const std::shared_ptr<Node> &parent, int render_priority = 0);

    explicit Controller(const std::shared_ptr<Node> &parent, int render_priority = 0) : Node(parent, render_priority) {}

    void render(EngineContext &ctx, sf::RenderStates &states) override;

    void update(EngineContext &ctx) override;

    int get_node_type() const override;

    virtual void on_key_press(sf::Event &event, EngineContext &ctx);

    virtual void on_key_release(sf::Event &event, EngineContext &ctx);

    virtual void on_mouse_press(sf::Event &event, EngineContext &ctx);

    virtual void on_mouse_release(sf::Event &event, EngineContext &ctx);

    virtual void on_mouse_moved(sf::Event &event, EngineContext &ctx);

    virtual void on_mouse_wheel_scrolled(sf::Event &event, EngineContext &ctx);
};


#endif //LOGISTICHELL_CONTROLLER_H
