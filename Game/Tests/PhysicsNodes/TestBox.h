//
// Created by EgorRychkov on 26.04.2025.
//

#ifndef LOGISTICHELL_TESTBOX_H
#define LOGISTICHELL_TESTBOX_H

#include "../../../Engine/Nodes/Base/ContainerNode.h"
#include "../../../Engine/Nodes/Render/Shapes/Polygon.h"
#include "../../../Engine/Nodes/Physics/CollisionPolygon.h"
#include "../../../Engine/Nodes/Render/Shapes/TexturedQuad.h"

class TestBox : public ContainerNode {
public:
    static std::shared_ptr<TestBox>
    create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<RigidBody> rigid_body, b2Vec2 grid,
           int render_priority = 0,
           int render_priority_layers = 10);


    explicit TestBox(std::shared_ptr<ContainerNode> parent, int render_priority = 0)
            : ContainerNode(parent, render_priority) {}

    void update(EngineContext &ctx) override;

    b2Vec2 vertices[4];
    std::vector<sf::Vector2f> step;
    std::shared_ptr<Polygon> render_polygon;
    std::shared_ptr<Polygon> center_polygon;
    std::shared_ptr<TexturedQuad> textured_quad;
    std::shared_ptr<CollisionPolygon> collision;
};


#endif //LOGISTICHELL_TESTBOX_H
