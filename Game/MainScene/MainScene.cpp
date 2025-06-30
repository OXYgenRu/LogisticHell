//
// Created by EgorRychkov on 27.04.2025.
//

#include <iostream>
#include "MainScene.h"
#include "../../Engine/Application.h"

void MainScene::init_tree(EngineContext &ctx) {
    auto scene = std::static_pointer_cast<MainScene>(shared_from_this());
    std::weak_ptr<MainScene> weak_scene = scene;
    ctx.app->set_background_color(sf::Color(1, 2, 74));
    blueprint_loader = std::make_shared<BlueprintLoader>();

//    Blueprint empty_block_blueprint({1, 1}, true, 0);
//    empty_block_blueprint.add_component()->set_block({0, 0},
//                                                     BlueprintBlock("empty_block::empty_block",
//                                                                    "void_block::void_block", 0,
//                                                                    true));
//    blueprint_loader->register_blueprint("empty_block", empty_block_blueprint);

    Blueprint construction_block_blueprint({1, 1}, 0);
    construction_block_blueprint.add_component()->set_block({0, 0},
                                                            BlueprintBlock(BlockType::BusyAttachable));
    std::shared_ptr<UnitProperties> construction_block_properties = std::make_shared<UnitProperties>(
            std::make_shared<UnitBehavior>());
    construction_block_properties->add_render_feature(
            UnitRenderFeature("0_0", "construction_block", {0, 0}, 0, {-0.5, -0.5}, {1, 1}, 0));
    blueprint_loader->register_unit("construction_block", construction_block_blueprint,
                                    construction_block_properties);

    Blueprint joint({1, 3}, 0);
    joint.add_component()->set_block({0, 0},
                                     BlueprintBlock(BlockType::BusyAttachable));
    joint.components[0]->set_block({0, 1},
                                   BlueprintBlock(BlockType::BusyLocked));
    joint.components[0]->set_body_type(ComponentBodyType::Static);
    joint.add_component()->set_block({0, 2},
                                     BlueprintBlock(BlockType::BusyAttachable));
    joint.components[1]->set_block({0, 1},
                                   BlueprintBlock(BlockType::BusyLocked));
    joint.components[1]->set_body_type(ComponentBodyType::Dynamic);
    std::shared_ptr<UnitProperties> joint_properties = std::make_shared<UnitProperties>(
            std::make_shared<UnitBehavior>());
    joint_properties->add_render_feature(UnitRenderFeature("0_0", "joint-0_0", {0, 0}, 1, {-0.5, -0.5}, {1, 1}, 0));
    joint_properties->add_render_feature(UnitRenderFeature("0_1", "joint-0_1", {0,
                                                                                0}, 1, {-0.5, 0.5}, {1, 1}, 0
    ));
    joint_properties->add_render_feature(UnitRenderFeature("0_2", "joint-0_2", {0,
                                                                                2}, 1, {-0.5, -0.5}, {1, 1}, 0));
    joint_properties->add_render_feature(
            UnitRenderFeature("0_0-background", "joint-background-0_0", {0, 0}, 0, {-0.5, -0.5}, {1, 1}, 0));
    joint_properties->add_render_feature(UnitRenderFeature("0_1-background", "joint-background-0_1", {0,
                                                                                                      2}, 0,
                                                           {-0.5, -1.5}, {1, 1}, 0
    ));
    joint_properties->add_render_feature(UnitRenderFeature("0_2-background", "joint-background-0_2", {0,
                                                                                                      2}, 0,
                                                           {-0.5, -0.5}, {1, 1}, 0));
    joint_properties->add_revolute_joint(BlueprintJoints::RevoluteJoint("1", {0, 1}, {0, 0}, {0, 2}));

    blueprint_loader->register_unit("joint", joint, joint_properties);


    Blueprint construction_block_static_blueprint({1, 1}, 0);
    construction_block_static_blueprint.add_component()->set_block({0, 0},
                                                                   BlueprintBlock(BlockType::BusyAttachable));
    construction_block_static_blueprint.components[0]->set_body_type(ComponentBodyType::Static);
    std::shared_ptr<UnitProperties> construction_block_static_properties = std::make_shared<UnitProperties>(
            std::make_shared<UnitBehavior>());
    construction_block_static_properties->add_render_feature(
            UnitRenderFeature("0_0", "construction_block", {0, 0}, 0, {-0.5, -0.5}, {1, 1}, 0));
    blueprint_loader->register_unit("static_construction_block", construction_block_static_blueprint,
                                    construction_block_static_properties);


    background_collider = UI::Collider::create(scene, 0);
    background_collider->set_vertices({{-800, -450},
                                       {800,  -450},
                                       {800,  450},
                                       {-800, 450}});
    world_camera = CameraNode::create(scene, ctx, 1);
    structures_system = std::make_shared<StructuresSystem>(scene, 0.2);
    world = World::create(world_camera, b2Vec2({0, -9.8}), 120, 1);
    dock_spawner = DockSpawner::create(world_camera, ctx, scene, {300, 300}, {10, 10}, 0.2, 0);

}

void MainScene::update(EngineContext &ctx) {
//    std::cout << 1 / ctx.last_frame_delta_time << '\n';

    b2World_Step(world->world_id, ctx.last_frame_delta_time, 1);
}