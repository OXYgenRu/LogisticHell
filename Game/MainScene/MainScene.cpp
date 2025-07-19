//
// Created by EgorRychkov on 27.04.2025.
//

#include <iostream>
#include "MainScene.h"
#include "../../Engine/Application.h"

class TestWPusher : public UnitBehavior {
public:
    void update(EngineContext &ctx, UnitApi &api) override {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            api.apply_force({0, 0}, {0, 0}, {0, 1000});
        }
    }
};

class TestDPusher : public UnitBehavior {
public:
    void update(EngineContext &ctx, UnitApi &api) override {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            api.apply_force({0, 0}, {0, 0}, {0, 1000});
        }
    }
};

class TestSPusher : public UnitBehavior {
public:
    void update(EngineContext &ctx, UnitApi &api) override {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            api.apply_force({0, 0}, {0, 0}, {0, 1000});
        }
    }
};

class TestAPusher : public UnitBehavior {
public:
    void update(EngineContext &ctx, UnitApi &api) override {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            api.apply_force({0, 0}, {0, 0}, {0, 1000});
        }
    }
};

void MainScene::init_tree(EngineContext &ctx) {
    auto scene = std::static_pointer_cast<MainScene>(shared_from_this());
    std::weak_ptr<MainScene> weak_scene = scene;
    ctx.app->set_background_color(sf::Color(1, 2, 74));
    blueprint_loader = std::make_shared<BlueprintLoader>();

    Blueprint construction_block_blueprint({1, 1}, 0);
    construction_block_blueprint.add_component()->set_block({0, 0},
                                                            BlueprintBlock(BlockType::BusyAttachable, 1000, 0.3));
    std::shared_ptr<UnitProperties> construction_block_properties = std::make_shared<UnitProperties>(
            std::make_shared<UnitBehavior>(), sf::Vector2i(0, 0), 0);
    construction_block_properties->add_render_feature(
            UnitRenderFeature("0_0", "construction_block", {0, 0}, 0, {-0.5, -0.5}, {1, 1}, 0));
    blueprint_loader->register_unit("construction_block", construction_block_blueprint,
                                    construction_block_properties);


    Blueprint test_w_pusher({1, 1}, 0);
    test_w_pusher.add_component()->set_block({0, 0},
                                             BlueprintBlock(BlockType::BusyAttachable, 1000, 0.3));
    std::shared_ptr<UnitProperties> test_w_pusher_behavior = std::make_shared<UnitProperties>(
            std::make_shared<TestWPusher>(), sf::Vector2i(0, 0), 0);
    test_w_pusher_behavior->add_render_feature(
            UnitRenderFeature("0_0", "test_w_pusher", {0, 0}, 0, {-0.5, -0.5}, {1, 1}, 0));
    blueprint_loader->register_unit("test_w_pusher", test_w_pusher,
                                    test_w_pusher_behavior);


    Blueprint test_d_pusher({1, 1}, 0);
    test_d_pusher.add_component()->set_block({0, 0},
                                             BlueprintBlock(BlockType::BusyAttachable, 1000, 0.3));
    std::shared_ptr<UnitProperties> test_d_pusher_behavior = std::make_shared<UnitProperties>(
            std::make_shared<TestDPusher>(), sf::Vector2i(0, 0), 0);
    test_d_pusher_behavior->add_render_feature(
            UnitRenderFeature("0_0", "test_d_pusher", {0, 0}, 0, {-0.5, -0.5}, {1, 1}, 0));
    blueprint_loader->register_unit("test_d_pusher", test_d_pusher,
                                    test_d_pusher_behavior);

    Blueprint test_s_pusher({1, 1}, 0);
    test_s_pusher.add_component()->set_block({0, 0},
                                             BlueprintBlock(BlockType::BusyAttachable, 1000, 0.3));
    std::shared_ptr<UnitProperties> test_s_pusher_behavior = std::make_shared<UnitProperties>(
            std::make_shared<TestSPusher>(), sf::Vector2i(0, 0), 0);
    test_s_pusher_behavior->add_render_feature(
            UnitRenderFeature("0_0", "test_s_pusher", {0, 0}, 0, {-0.5, -0.5}, {1, 1}, 0));
    blueprint_loader->register_unit("test_s_pusher", test_s_pusher,
                                    test_s_pusher_behavior);

    Blueprint test_a_pusher({1, 1}, 0);
    test_a_pusher.add_component()->set_block({0, 0},
                                             BlueprintBlock(BlockType::BusyAttachable, 1000, 0.3));
    std::shared_ptr<UnitProperties> test_a_pusher_behavior = std::make_shared<UnitProperties>(
            std::make_shared<TestAPusher>(), sf::Vector2i(0, 0), 0);
    test_a_pusher_behavior->add_render_feature(
            UnitRenderFeature("0_0", "test_a_pusher", {0, 0}, 0, {-0.5, -0.5}, {1, 1}, 0));
    blueprint_loader->register_unit("test_a_pusher", test_a_pusher,
                                    test_a_pusher_behavior);


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
    std::shared_ptr<UnitProperties> joint_properties = std::make_shared<UnitProperties>(
            std::make_shared<UnitBehavior>(), sf::Vector2i(0, 0), 0);
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
                                                                   BlueprintBlock(BlockType::BusyAttachable, 1000,
                                                                                  0.3));
    construction_block_static_blueprint.components[0]->set_body_type(ComponentBodyType::Static);
    std::shared_ptr<UnitProperties> construction_block_static_properties = std::make_shared<UnitProperties>(
            std::make_shared<UnitBehavior>(), sf::Vector2i(0, 0), 0);
    construction_block_static_properties->add_render_feature(
            UnitRenderFeature("0_0", "construction_block", {0, 0}, 0, {-0.5, -0.5}, {1, 1}, 0));
    blueprint_loader->register_unit("static_construction_block", construction_block_static_blueprint,
                                    construction_block_static_properties);


    background_collider = UI::Collider::create(scene, "BackgroundCollider");
    background_collider->set_vertices({{-800, -450},
                                       {800,  -450},
                                       {800,  450},
                                       {-800, 450}});
    world_camera = CameraNode::create(scene, ctx, "WorldCamera", 1);
    structures_system = StructuresSystem::create(scene, scene, 0.2, "StructuresSystem");
    world = World::create(world_camera, b2Vec2({0, 0}), 120, "World", 1);
    docks_system = DocksSystem::create(scene, scene, "DockSystem");
    docks_system->create_dock_spawner(ctx, {300, 300}, {20, 20}, 0.2);
}

void MainScene::update(EngineContext &ctx) {
    b2World_Step(world->world_id, ctx.last_frame_delta_time, 4);
}