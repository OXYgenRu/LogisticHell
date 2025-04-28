//
// Created by EgorRychkov on 27.04.2025.
//

#ifndef LOGISTICHELL_TESTCONTROLLER_H
#define LOGISTICHELL_TESTCONTROLLER_H


#include "../../../Engine/Nodes/Control/Controller.h"
#include "box2d/box2d.h"

class TestController : public Controller {
public:
    static std::shared_ptr<TestController>
    create(std::shared_ptr<ContainerNode> parent, b2BodyId body, int render_priority = 0);

    explicit TestController(std::shared_ptr<ContainerNode> parent, int render_priority = 0) : Controller(parent,
                                                                                                         render_priority) {}

    void update(EngineContext &ctx) override;

    b2BodyId body;

};


#endif //LOGISTICHELL_TESTCONTROLLER_H
