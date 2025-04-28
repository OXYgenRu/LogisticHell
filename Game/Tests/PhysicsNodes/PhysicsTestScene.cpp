//
// Created by EgorRychkov on 26.04.2025.
//

#include "PhysicsTestScene.h"
#include "TestBox.h"
#include "iostream"
#include "TestController.h"

void PhysicsTestScene::init_tree(EngineContext &ctx) {
    auto scene = shared_from_this();
    camera = CameraNode::create(scene, ctx);
    world = World::create(camera, b2Vec2({0, 0}), 60);

    b2BodyDef body_def = b2DefaultBodyDef();
    body_def.type = b2_dynamicBody;
    body_def.position = b2Vec2({0, 0});

    body = RigidBody::create(world, world, body_def);

    b2Body_SetLinearDamping(body->body, 0.9);
    b2Body_SetAngularDamping(body->body, 0.9);
    for (int i = 0; i < 5 * 10; i++) {
        for (int j = 0; j < 5 * 2; j++) {
            TestBox::create(body, body, {float(i * 0.2), float(j * 0.2)});
        }
    }
    body_def.type = b2_staticBody;
    body_def.position = b2Vec2({-15, 1});

    body2 = RigidBody::create(world, world, body_def);
    box2 = TestBox::create(body2, body2, {0, 0});

    this->controller = TestController::create(camera, body->body);
    Polygon::create(camera)->set_polygon();
}

void PhysicsTestScene::update(EngineContext &ctx) {
    std::cout << 1 / ctx.last_frame_delta_time << '\n';
    b2Vec2 c = b2Body_GetLocalCenterOfMass(body->body);
//    b2Vec2 point = this->body->b2_get_world_point(c,ctx);

    b2World_Step(world->world_id, ctx.last_frame_delta_time, 1);
    this->camera->set_camera_target(this->body->sf_get_world_point(c, ctx));
}