//
// Created by EgorRychkov on 27.04.2025.
//

#include <iostream>
#include "MainScene.h"
#include "../../Engine/Application.h"
#include "Structure/Component/Component.h"

void MainScene::init_tree(EngineContext &ctx) {
    auto scene = shared_from_this();
    ctx.app->texture_atlas->register_texture("empty_block", "blocks/EmptyGridBlockBlue.png");
    ctx.app->texture_atlas->register_texture("discarded_block", "blocks/DiscardedGridBlockBlue.png");
    ctx.app->set_background_color(sf::Color(1, 2, 74));
    world = World::create(scene, b2Vec2({0, 0}), 240);
    dock = Dock::create(world, world, {200, 600}, sf::Vector2i({5, 5,}), 0.2, ctx);
}

void MainScene::update(EngineContext &ctx) {
//    std::cout << 1 / ctx.last_frame_delta_time << '\n';

    b2World_Step(world->world_id, ctx.last_frame_delta_time, 1);
}