//
// Created by EgorRychkov on 07.04.2025.
//
#include "iostream"
#include "Engine/Application.h"
#include "Engine/Nodes/Base/Node.h"

#include "Engine/Nodes/Control/Controller.h"
#include "Game/Tests/UITest/UIScene.h"
#include "box2d/box2d.h"
#include "Game/MainScene/MainScene.h"


int main() {
    Application app(sf::VideoMode(1600, 900), "SignalsFromTheDepth", 165);
    app.scene_system->registerScene(0, []() { return UIScene::create("UIScene"); });
    app.scene_system->registerScene(1, []() { return MainScene::create("MainScene"); });
    app.set_new_scene(1);

    app.texture_atlas->register_texture("empty_block", "blocks/EmptyGridBlockBlue.png");
    app.texture_atlas->register_texture("white", "blocks/WhiteStandart.png");
    app.texture_atlas->register_texture("discarded_block", "blocks/DiscardedGridBlockBlue.png");
    app.texture_atlas->register_texture("icon", "blocks/Icon.png");
    app.texture_atlas->register_texture("construction_block", "blocks/TestConstructionBlock.png");
    app.texture_atlas->register_texture("hull", "blocks/Hull.png");
    app.texture_atlas->register_texture("beam", "blocks/BeamBlock.png");
    app.texture_atlas->register_texture("light_construction", "blocks/LightConstructionBlock.png");
    app.texture_atlas->register_texture("middle_construction", "blocks/MiddleConstructionBlock.png");
    app.texture_atlas->register_texture("heavy_construction", "blocks/HeavyConstructionBlock.png");

    app.texture_atlas->register_texture("void_block", "blocks/VoidBLock.png");
    app.texture_atlas->register_texture("busy_grid_block", "blocks/BusyGridBlockBlue.png");
    app.texture_atlas->register_texture("selected_grid_block", "blocks/SelectedGridBlock.png");
    app.texture_atlas->register_texture("attach_icon", "blocks/Attach_icon.png");
    app.texture_atlas->register_texture("remove_icon", "blocks/Remove_icon.png");
    app.texture_atlas->register_texture("assemble_icon", "blocks/Assemble_icon.png");

    app.texture_atlas->register_texture("joint-0_0", "units/joint/Joint-3.png");
    app.texture_atlas->register_texture("joint-0_1", "units/joint/Joint-2.png");
    app.texture_atlas->register_texture("joint-0_2", "units/joint/Joint-1.png");
    app.texture_atlas->register_texture("joint-background-0_0", "units/joint/Joint-background3.png");
    app.texture_atlas->register_texture("joint-background-0_1", "units/joint/Joint-background2.png");
    app.texture_atlas->register_texture("joint-background-0_2", "units/joint/Joint-background1.png");
    app.texture_atlas->register_texture("quit_dock", "blocks/QuitDock.png");

    app.texture_atlas->register_texture("test_w_pusher", "blocks/TestWPusher.png");
    app.texture_atlas->register_texture("test_d_pusher", "blocks/TestDPusher.png");
    app.texture_atlas->register_texture("test_s_pusher", "blocks/TestSPusher.png");
    app.texture_atlas->register_texture("test_a_pusher", "blocks/TestAPusher.png");
    app.start();

    
    return 0;
}