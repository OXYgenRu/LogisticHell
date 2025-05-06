//
// Created by EgorRychkov on 26.04.2025.
//

#include "TestBox.h"
#include "../../../Engine/Nodes/Base/ContainerNode.h"
#include "../../../Engine/Nodes/Render/Shapes/Polygon.h"
#include "../../../Engine/Nodes/Physics/CollisionPolygon.h"
#include "../../../Engine/Application.h"
#include "PhysicsTestScene.h"

std::shared_ptr<TestBox>
TestBox::create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<RigidBody> rigid_body, b2Vec2 grid,
                int render_priority,
                int render_priority_layers) {
    auto node = std::make_shared<TestBox>(parent, render_priority);

//    node->render_polygon = Polygon::create(node);
//    node->render_polygon->set_polygon();
    node->center_polygon = Polygon::create(node);
    node->center_polygon->set_polygon();
    node->center_polygon->polygon.setFillColor(sf::Color::Yellow);
    node->textured_quad = TexturedQuad::create(node);
//    node->textured_quad->texture.loadFromFile("TestConstructionBlock.png");

    node->textured_quad->quad[0].texCoords = sf::Vector2f(0.f, 0.f);
    node->textured_quad->quad[1].texCoords = sf::Vector2f(0.f, 32.f);
    node->textured_quad->quad[2].texCoords = sf::Vector2f(32.f, 32.f);
    node->textured_quad->quad[3].texCoords = sf::Vector2f(32.f, 0.f);

    node->step = {{2,  2},
                  {-2, 2},
                  {-2, -2},
                  {2,  -2}};

    b2ShapeDef shape_def = b2DefaultShapeDef();
    shape_def.density = 300.0f;
    shape_def.material.friction = 0.3f;

    b2Polygon polygon;
    node->vertices[0] = {grid.x + -0.1f, 0.1f + grid.y};
    node->vertices[1] = {grid.x + -0.1f, -0.1f + grid.y};
    node->vertices[2] = {grid.x + 0.1f, -0.1f + grid.y};
    node->vertices[3] = {grid.x + 0.1f, 0.1f + grid.y};
    b2Hull hull = b2ComputeHull(node->vertices, 4);


    polygon = b2MakePolygon(&hull, 0);
    node->collision = CollisionPolygon::create(node, rigid_body, shape_def, polygon);
    parent->add_node(node);
    return node;
}

void TestBox::update(EngineContext &ctx) {
    auto scene = std::static_pointer_cast<PhysicsTestScene>(ctx.app->scene_system->currentScene);
    auto rigid_body = this->collision->rigid_body.lock();
    for (int i = 0; i < this->collision->polygon.count; i++) {
//        this->render_polygon->polygon.setPoint(i, );
        this->textured_quad->quad[i].position = rigid_body->sf_get_world_point(this->vertices[i],
                                                                               ctx);
//        b2Vec2 c = this->vertices[i] +
//                   b2Vec2({step[i].x / rigid_body->pixel_per_meter, step[i].y / rigid_body->pixel_per_meter});
//        this->center_polygon->polygon.setPoint(i, rigid_body->sf_get_world_point(
//                c, ctx));
    }

}