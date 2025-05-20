//
// Created by EgorRychkov on 22.04.2025.
//

#ifndef LOGISTICHELL_TESTCOLLIDER_H
#define LOGISTICHELL_TESTCOLLIDER_H

#include "iostream"

#include "../../../Engine/Nodes/UI/Collider.h"


class TestCollider : public UI::Collider {
public:

    static std::shared_ptr<TestCollider> create(std::shared_ptr<ContainerNode> parent, int render_priority = 0);

    explicit TestCollider(std::shared_ptr<ContainerNode> parent, int render_priority = 0) : UI::Collider(parent,
                                                                                                       render_priority) {}

//    void handle_mouse_press(sf::Event &event, EngineContext &ctx) override;
};


#endif //LOGISTICHELL_TESTCOLLIDER_H
