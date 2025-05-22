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
    blueprint_loader = std::make_shared<BlueprintLoader>();

    Blueprint empty_block_blueprint({1, 1}, true, 0);
    empty_block_blueprint.add_component()->set_block({0, 0},
                                                     BlueprintBlock("empty_block::empty_block", {0, 0}, {1, 1}, 0));
    blueprint_loader->register_blueprint("empty_block", empty_block_blueprint);

    Blueprint construction_block_blueprint({1, 1}, true, 0);
    construction_block_blueprint.add_component()->set_block({0, 0},
                                                            BlueprintBlock("construction_block::construction_block",
                                                                           {0, 0}, {1, 1}, 0));
    blueprint_loader->register_blueprint("construction_block", construction_block_blueprint);

    Blueprint big_construction({2, 2}, true, 0);
    big_construction.add_component()->set_block({0, 0},
                                                BlueprintBlock("heavy_construction::heavy_construction",
                                                               {0, 0}, {2, 2}, 0));
    big_construction.components[0]->set_block({1, 0},
                                              BlueprintBlock("heavy_construction::heavy_construction",
                                                             {1, 0}, {2, 2}, 0));
    big_construction.add_component()->set_block({0, 1},
                                                BlueprintBlock("light_construction::light_construction",
                                                               {2, 0}, {2, 2}, 0));
    big_construction.components[1]->set_block({1, 1},
                                              BlueprintBlock("light_construction::light_construction",
                                                             {1, 1}, {2, 2}, 0));
    blueprint_loader->register_blueprint("big_construction", big_construction);


    Blueprint light_construction({1, 1}, true, 0);
    light_construction.add_component()->set_block({0, 0},
                                                            BlueprintBlock("light_construction::light_construction",
                                                                           {0, 0}, {1, 1}, 0));
    blueprint_loader->register_blueprint("light_construction", light_construction);

    Blueprint beam({1, 1}, true, 0);
    beam.add_component()->set_block({0, 0},
                                                            BlueprintBlock("beam::beam",
                                                                           {0, 0}, {1, 1}, 0));
    blueprint_loader->register_blueprint("beam", beam);

    block_factory = std::make_shared<BlockFactory>();
    block_factory->register_block("light_construction", "light_construction", "light_construction");
    block_factory->register_block("heavy_construction", "heavy_construction", "heavy_construction");
    block_factory->register_block("empty_block", "empty_block", "empty_block");
    block_factory->register_block("discarded_block", "discarded_block", "discarded_block");
    block_factory->register_block("construction_block", "construction_block", "construction_block");
    block_factory->register_block("test_unit", "construction_block", "construction_block");
    block_factory->register_block("void_block", "void_block", "void_block");
    block_factory->register_block("busy_grid_block", "busy_grid_block", "busy_grid_block");
    block_factory->register_block("icon", "icon", "icon");
    block_factory->register_block("beam", "beam", "beam");
    block_factory->register_block("selected_grid_block", "selected_grid_block", "selected_grid_block");

    world = World::create(scene, b2Vec2({0, 0}), 240);
    dock = Dock::create(world, ctx, world, {200, 600}, sf::Vector2i({10, 10}), 0.2, blueprint_loader, block_factory);
}

void MainScene::update(EngineContext &ctx) {
//    std::cout << 1 / ctx.last_frame_delta_time << '\n';

    b2World_Step(world->world_id, ctx.last_frame_delta_time, 1);
}