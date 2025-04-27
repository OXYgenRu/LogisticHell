//
// Created by EgorRychkov on 26.04.2025.
//

#include "TestBox.h"
#include "../../../Engine/Nodes/Base/ContainerNode.h"
#include "../../../Engine/Nodes/Render/Shapes/Polygon.h"
#include "../../../Engine/Nodes/Physics/CollisionPolygon.h"
#include "../../../Engine/Application.h"

std::shared_ptr<TestBox>
TestBox::create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<RigidBody> rigid_body, b2Vec2 grid,
                int render_priority,
                int render_priority_layers) {
    auto node = std::make_shared<TestBox>(parent, render_priority);

    node->step = {{2,  2},
                  {-2, 2},
                  {-2, -2},
                  {2,  -2}};

    node->render_polygon = Polygon::create(node);
    node->render_polygon->set_polygon();
    node->center_polygon = Polygon::create(node);
    node->center_polygon->set_polygon();
    node->center_polygon->polygon.setFillColor(sf::Color::Yellow);

    b2ShapeDef shape_def = b2DefaultShapeDef();
    shape_def.density = 1.0f;
    shape_def.material.friction = 0.3f;

    b2Polygon polygon;

    b2Vec2 vertices[4];
    vertices[0] = {grid.x + -0.2f, -0.2f + grid.y};
    vertices[1] = {grid.x + 0.2f, -0.2f + grid.y};
    vertices[2] = {grid.x + 0.2f, 0.2f + grid.y};
    vertices[3] = {grid.x + -0.2f, 0.2f + grid.y};
    b2Hull hull = b2ComputeHull(vertices, 4);

    polygon = b2MakePolygon(&hull, 0);
    node->collision = CollisionPolygon::create(node, rigid_body, shape_def, polygon);
    parent->add_node(node);
    return node;
}

void TestBox::update(EngineContext &ctx) {
    for (int i = 0; i < this->collision->polygon.count; ++i) {
        b2Vec2 localVertex = this->collision->polygon.vertices[i];
        b2Vec2 worldVertex = b2Body_GetWorldPoint(this->collision->rigid_body, localVertex);
        this->render_polygon->polygon.setPoint(i, sf::Vector2f((worldVertex.x) * 60,
                                                               (ctx.app->window->getSize().y - worldVertex.y * 60)));
        worldVertex = b2Body_GetWorldPoint(this->collision->rigid_body,
                                           localVertex + b2Vec2({step[i].x / 60, step[i].y / 60}));
        this->center_polygon->polygon.setPoint(i, sf::Vector2f((worldVertex.x) * 60,
                                                               (ctx.app->window->getSize().y - worldVertex.y * 60)));

    }
}