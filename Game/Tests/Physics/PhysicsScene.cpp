//
// Created by EgorRychkov on 24.04.2025.
//

#include "PhysicsScene.h"
#include "box2d/box2d.h"
#include "iostream"

void PhysicsScene::init_tree(EngineContext &ctx) {
    auto scene = shared_from_this();
    camera = CameraNode::create(scene, ctx);
    world = World::create(camera, b2Vec2({0, -9.8}), 60);
    box = BoxExample::create(camera, world->world_id);
}

void PhysicsScene::update(EngineContext &ctx) {
//    std::cout << 1 / ctx.last_frame_delta_time << '\n';
    b2World_Step(world->world_id, float(float(1) / 60), 3);
}