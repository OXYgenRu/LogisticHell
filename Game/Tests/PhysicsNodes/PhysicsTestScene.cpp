//
// Created by EgorRychkov on 26.04.2025.
//

#include "PhysicsTestScene.h"
#include "TestBox.h"

void PhysicsTestScene::init_tree(EngineContext &ctx) {
    auto scene = shared_from_this();
    camera = CameraNode::create(scene, ctx);
    world = World::create(camera, b2Vec2({0, -9.8}), 60);

    b2BodyDef body_def = b2DefaultBodyDef();
    body_def.type = b2_dynamicBody;
    body_def.position = b2Vec2({3.2, 15});

    body = RigidBody::create(world, world, body_def);

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 3; j++) {
            TestBox::create(body, body, {float(i * 0.4), float(j * 0.4)});
        }
    }
//    box1 = TestBox::create(body, body, {0, 0});
//    box3 = TestBox::create(body, body, {2, 0});

    body_def.type = b2_staticBody;
    body_def.position = b2Vec2({4, 1});

    body2 = RigidBody::create(world, world, body_def);
    box2 = TestBox::create(body2, body2, {0, 0});
}

void PhysicsTestScene::update(EngineContext &ctx) {
    b2World_Step(world->world_id, ctx.last_frame_delta_time, 1);
}