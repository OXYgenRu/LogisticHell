//
// Created by EgorRychkov on 27.04.2025.
//

#include <iostream>
#include "MainScene.h"
#include "../../Engine/Application.h"
#include "World/GameWorld.h"

class TestWPusher : public UnitBehavior {
public:
    void update(const unsigned int &unit_id, float last_frame_delta_time, Api &api) override {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            api.units->apply_force(unit_id, {0, 0}, {0, 0}, {0, 1000});
        }
    }
};

class TestDPusher : public UnitBehavior {
public:
    void update(const unsigned int &unit_id, float last_frame_delta_time, Api &api) override {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            api.units->apply_force(unit_id, {0, 0}, {0, 0}, {0, 1000});
        }
    }
};

class TestSPusher : public UnitBehavior {
public:
    void update(const unsigned int &unit_id, float last_frame_delta_time, Api &api) override {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            api.units->apply_force(unit_id, {0, 0}, {0, 0}, {0, 1000});
        }
    }
};

class TestAPusher : public UnitBehavior {
public:
    void update(const unsigned int &unit_id, float last_frame_delta_time, Api &api) override {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            api.units->apply_force(unit_id, {0, 0}, {0, 0}, {0, 1000});
        }
    }
};

void MainScene::init_tree(EngineContext &ctx) {
    auto scene = std::static_pointer_cast<MainScene>(shared_from_this());
    std::weak_ptr<MainScene> weak_scene = scene;
    ctx.app->set_background_color(sf::Color(1, 2, 74));
    inspector = Inspector::create(scene, ctx, "Inspector", 100);
    inspector->set_position({-ctx.app->get_window_size().x / 2, -ctx.app->get_window_size().y / 2});
    world_camera = CameraNode::create(scene, ctx, "WorldCamera", 1);
    world = GameWorld::create(world_camera, scene, node_id, 1);


    Blueprint construction_block_blueprint({1, 1}, 0);
    construction_block_blueprint.add_component()->set_block({0, 0},
                                                            BlueprintBlock(BlockType::BusyAttachable, 1000, 0.3));
    std::shared_ptr<UnitProperties> construction_block_properties = std::make_shared<UnitProperties>(sf::Vector2i(0, 0),
                                                                                                     0);
    construction_block_properties->add_render_feature(
            UnitRenderFeature("0_0", "construction_block", {0, 0}, 0, {-0.5, -0.5}, {1, 1}, 0));
    world->get_blueprints_loader()->register_unit("construction_block", construction_block_blueprint,
                                                  construction_block_properties, std::make_shared<UnitBehavior>());


    Blueprint test_w_pusher({1, 1}, 0);
    test_w_pusher.add_component()->set_block({0, 0},
                                             BlueprintBlock(BlockType::BusyAttachable, 1000, 0.3));
    std::shared_ptr<UnitProperties> test_w_pusher_properties = std::make_shared<UnitProperties>(sf::Vector2i(0, 0), 0);
    test_w_pusher_properties->add_render_feature(
            UnitRenderFeature("0_0", "test_w_pusher", {0, 0}, 0, {-0.5, -0.5}, {1, 1}, 0));
    world->get_blueprints_loader()->register_unit("test_w_pusher", test_w_pusher, test_w_pusher_properties,
                                                  std::make_shared<TestWPusher>());


    Blueprint test_d_pusher({1, 1}, 0);
    test_d_pusher.add_component()->set_block({0, 0},
                                             BlueprintBlock(BlockType::BusyAttachable, 1000, 0.3));
    std::shared_ptr<UnitProperties> test_d_pusher_properties = std::make_shared<UnitProperties>(sf::Vector2i(0, 0), 0);
    test_d_pusher_properties->add_render_feature(
            UnitRenderFeature("0_0", "test_d_pusher", {0, 0}, 0, {-0.5, -0.5}, {1, 1}, 0));
    world->get_blueprints_loader()->register_unit("test_d_pusher", test_d_pusher,
                                                  test_d_pusher_properties, std::make_shared<TestDPusher>());

    Blueprint test_s_pusher({1, 1}, 0);
    test_s_pusher.add_component()->set_block({0, 0},
                                             BlueprintBlock(BlockType::BusyAttachable, 1000, 0.3));
    std::shared_ptr<UnitProperties> test_s_pusher_properties = std::make_shared<UnitProperties>(sf::Vector2i(0, 0), 0);
    test_s_pusher_properties->add_render_feature(
            UnitRenderFeature("0_0", "test_s_pusher", {0, 0}, 0, {-0.5, -0.5}, {1, 1}, 0));
    world->get_blueprints_loader()->register_unit("test_s_pusher", test_s_pusher,
                                                  test_s_pusher_properties, std::shared_ptr<TestSPusher>());

    Blueprint test_a_pusher({1, 1}, 0);
    test_a_pusher.add_component()->set_block({0, 0},
                                             BlueprintBlock(BlockType::BusyAttachable, 1000, 0.3));
    std::shared_ptr<UnitProperties> test_a_pusher_properties = std::make_shared<UnitProperties>(sf::Vector2i(0, 0), 0);
    test_a_pusher_properties->add_render_feature(
            UnitRenderFeature("0_0", "test_a_pusher", {0, 0}, 0, {-0.5, -0.5}, {1, 1}, 0));
    world->get_blueprints_loader()->register_unit("test_a_pusher", test_a_pusher,
                                                  test_a_pusher_properties, std::shared_ptr<TestAPusher>());


    Blueprint joint({1, 3}, 0);
    joint.add_component()->set_block({0, 0},
                                     BlueprintBlock(BlockType::BusyAttachable, 1000, 0.3));
    joint.components[0]->set_block({0, 1},
                                   BlueprintBlock(BlockType::BusyLocked, 1000, 0.3));
    joint.components[0]->set_body_type(ComponentBodyType::Static);
    joint.add_component()->set_block({0, 2},
                                     BlueprintBlock(BlockType::BusyAttachable, 1000, 0.3));
    joint.components[1]->set_block({0, 1},
                                   BlueprintBlock(BlockType::BusyLocked, 1000, 0.3));
    joint.components[1]->set_body_type(ComponentBodyType::Dynamic);
    std::shared_ptr<UnitProperties> joint_properties = std::make_shared<UnitProperties>(sf::Vector2i(0, 0), 0);
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

    world->get_blueprints_loader()->register_unit("joint", joint, joint_properties, std::shared_ptr<UnitBehavior>());


    Blueprint construction_block_static_blueprint({1, 1}, 0);
    construction_block_static_blueprint.add_component()->set_block({0, 0},
                                                                   BlueprintBlock(BlockType::BusyAttachable, 1000,
                                                                                  0.3));
    construction_block_static_blueprint.components[0]->set_body_type(ComponentBodyType::Dynamic);
    std::shared_ptr<UnitProperties> construction_block_static_properties = std::make_shared<UnitProperties>(
            sf::Vector2i(0, 0), 0);
    construction_block_static_properties->add_render_feature(
            UnitRenderFeature("0_0", "construction_block", {0, 0}, 0, {-0.5, -0.5}, {1, 1}, 0));
    world->get_blueprints_loader()->register_unit("static_construction_block", construction_block_static_blueprint,
                                                  construction_block_static_properties,
                                                  std::shared_ptr<UnitBehavior>());


    background_collider = UI::Collider::create(scene, "BackgroundCollider");
    background_collider->set_vertices({{-800, -450},
                                       {800,  -450},
                                       {800,  450},
                                       {-800, 450}});

    world->get_docks_system()->create_dock_spawner(ctx, {300, 300}, {20, 20}, 0.2);
    world->get_docks_system()->create_dock_spawner(ctx, {-300, 300}, {5, 5}, 0.2);
}

void MainScene::update(EngineContext &ctx) {
    b2World_Step(world->get_world_id(), ctx.last_frame_delta_time, 4);
}