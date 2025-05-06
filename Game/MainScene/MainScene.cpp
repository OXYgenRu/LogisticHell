//
// Created by EgorRychkov on 27.04.2025.
//

#include <iostream>
#include "MainScene.h"
#include "../../Engine/Application.h"
#include "Structure/Component/Component.h"

void MainScene::init_tree(EngineContext &ctx) {
    auto scene = shared_from_this();
    ctx.app->set_background_color(sf::Color(1, 2, 74));
    world = World::create(scene, b2Vec2({0, 0}), 240);
    dock = Dock::create(world, world,{200,600},sf::Vector2i({5,5,}),0.2,ctx);
//    structure = Structure::create(nullptr, world, sf::Vector2f({100, 300}), sf::Vector2i({4, 4}), 0.2);
//    dock->set_structure(structure);


//    b2BodyDef body_def = b2DefaultBodyDef();
//    body_def.type = b2_dynamicBody;
//    body_def.position = b2Vec2({0, 0});

//    b2Body_SetAngularDamping(structure->body, 1);
//    b2Body_SetLinearDamping(structure->body, 1);
//    for (int i = 0; i < 6; i++) {
//        for (int j = 0; j < 6; j++) {
//            structure->set_block(sf::Vector2i({i, j}));
//        }
//    }
//
//
//    body_def.type = b2_staticBody;
//    body_def.position = b2Vec2({10, 2});
//    static_structure = Structure::create(world, world, body_def, sf::Vector2i({3, 3}), 0.2);
//    b2Body_SetAngularDamping(static_structure->body, 1);
//    b2Body_SetLinearDamping(static_structure->body, 1);
//
//
//    for (int i = 0; i < 2; i++) {
//        for (int j = 0; j < 2; j++) {
//            static_structure->set_block(sf::Vector2i({i, j}));
//        }
//    }


//    test_controller = TestController::create(scene, structure->body);

}

void MainScene::update(EngineContext &ctx) {
//    std::cout << 1 / ctx.last_frame_delta_time << '\n';

    b2World_Step(world->world_id, ctx.last_frame_delta_time, 1);
}