//
// Created by EgorRychkov on 20.04.2025.
//

#ifndef LOGISTICHELL_UICOLLIDER_H
#define LOGISTICHELL_UICOLLIDER_H

#include "../Base/ContentNode.h"
#include "SFML/Graphics.hpp"

class UICollider : public ContentNode {
public:
    static std::shared_ptr<UICollider> create(std::shared_ptr<ContainerNode> parent, int render_priority = 0);

    explicit UICollider(std::shared_ptr<ContainerNode> parent, int render_priority = 0) : ContentNode(parent,
                                                                                                      render_priority) {}

    void render(EngineContext &ctx) override;

    void update(EngineContext &ctx) override;

    int get_node_type() const override;

    virtual void on_mouse_press(sf::Event &event, EngineContext &ctx);

    virtual void on_mouse_release(sf::Event &event, EngineContext &ctx);

    virtual void on_mouse_moved(sf::Event &event, EngineContext &ctx);

    std::vector<sf::Vector2f> vertices;
};


#endif //LOGISTICHELL_UICOLLIDER_H
