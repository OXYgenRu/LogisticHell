//
// Created by EgorRychkov on 28.04.2025.
//

#ifndef LOGISTICHELL_BASEBLOCK_H
#define LOGISTICHELL_BASEBLOCK_H


#include "../../../../Engine/Nodes/Physics/RigidBody.h"
#include "../../../../Engine/Nodes/Physics/CollisionPolygon.h"
#include "../../../../Engine/Nodes/Render/Shapes/TexturedQuad.h"

class Component;

class BaseBlock : public Node {
public:
    static std::shared_ptr<BaseBlock>
    create(const std::shared_ptr<Node> &parent, std::shared_ptr<RigidBody> rigid_body, b2Vec2 grid_position,
           float cell_size,
           int render_priority = 0,
           int render_priority_layers = 10);


    explicit BaseBlock(const std::shared_ptr<Node> &parent, int render_priority = 0)
            : Node(parent, render_priority) {}

    static void setup(std::shared_ptr<BaseBlock> node, b2Vec2 grid, std::shared_ptr<RigidBody> rigid_body,
                      int render_priority_layers, float cell_size);

    void update(EngineContext &ctx) override;



    b2Vec2 vertices[4];
    b2Vec2 grid_position;
    std::shared_ptr<CollisionPolygon> collision_polygon;
    std::shared_ptr<TexturedQuad> textured_quad;

};


#endif //LOGISTICHELL_BASEBLOCK_H
