//
// Created by EgorRychkov on 24.04.2025.
//

#ifndef LOGISTICHELL_BOXEXAMPLE_H
#define LOGISTICHELL_BOXEXAMPLE_H


#include "../../../Engine/Nodes/Base/ContainerNode.h"

#include "box2d/box2d.h"
#include "../../../Engine/Nodes/Physics/World.h"
#include "../../../Engine/Nodes/Render/Shapes/Polygon.h"

class BoxExample : public ContainerNode {
public:
    static std::shared_ptr<BoxExample>
    create(std::shared_ptr<ContainerNode> parent, b2WorldId world, int render_priority = 0,
           int render_priority_layers = 10);


    explicit BoxExample(std::shared_ptr<ContainerNode> parent, int render_priority = 0) : ContainerNode(parent,
                                                                                                        render_priority) {}

    void update(EngineContext &ctx) override;

    b2BodyDef body_def = b2DefaultBodyDef();
    b2BodyId body;
    b2Polygon body_polygon;

    std::shared_ptr<Polygon> render_polygon;
};


#endif //LOGISTICHELL_BOXEXAMPLE_H

