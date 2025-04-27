//
// Created by EgorRychkov on 24.04.2025.
//

#include "BoxExample.h"
#include "../../../Engine/Nodes/Physics/World.h"
#include "../../../Engine/Nodes/Render/Shapes/Polygon.h"
#include "../../../Engine/Application.h"

std::shared_ptr<BoxExample>
BoxExample::create(std::shared_ptr<ContainerNode> parent,b2WorldId world, int render_priority,
                   int render_priority_layers) {
    auto node = std::make_shared<BoxExample>(parent, render_priority);

    node->set_render_layers_count(render_priority_layers + 1);
    node->body_def.type = b2_staticBody;
    node->body_def.position = b2Vec2({5, 5});
    node->body = b2CreateBody(world, &node->body_def);

    node->body_polygon = b2MakeBox(1.0f, 1.0f);
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    groundShapeDef.density = 1.0f;
    groundShapeDef.material.friction = 0.3f;
    b2CreatePolygonShape(node->body, &groundShapeDef, &node->body_polygon);

    node->render_polygon = Polygon::create(node, 0);
    std::vector<sf::Vector2f> b = {{100, 100},
                                   {200, 100},
                                   {200, 200},
                                   {100, 200}};
    node->render_polygon->set_polygon(b);

    parent->add_node(node);
    return node;
}

void BoxExample::update(EngineContext &ctx) {
    for (int i = 0; i < this->body_polygon.count; ++i) {
        b2Vec2 localVertex = this->body_polygon.vertices[i];
        b2Vec2 worldVertex = b2Body_GetWorldPoint(body, localVertex);
        this->render_polygon->polygon.setPoint(i, sf::Vector2f((worldVertex.x) * 60,
                                                               (ctx.app->window->getSize().y - worldVertex.y * 60)));
    }
}