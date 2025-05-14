//
// Created by EgorRychkov on 07.04.2025.
//
#include "iostream"
#include "Engine/Application.h"
#include "Engine/Nodes/Base/Node.h"
#include "Engine/Nodes/Base/ContainerNode.h"
#include "Engine/Nodes/Base/ContentNode.h"
#include "Engine/Nodes/Render/Shapes/Polygon.h"
#include "Engine/Nodes/Control/Controller.h"
#include "Game/Tests/UITest/UIScene.h"
#include "Game/Tests/Physics/PhysicsScene.h"
#include "Game/Tests/PhysicsNodes/PhysicsTestScene.h"
#include "box2d/box2d.h"
#include "Game/MainScene/MainScene.h"


int main() {
    Application app(sf::VideoMode(1600, 900), "LogisticHell", 165);
    app.scene_system->registerScene(0, []() { return UIScene::create(10); });
    app.scene_system->registerScene(1, []() { return PhysicsScene::create(10); });
    app.scene_system->registerScene(2, []() { return PhysicsTestScene::create(10); });
    app.scene_system->registerScene(3, []() { return MainScene::create(10); });
    app.set_new_scene(3);

    app.texture_atlas->register_texture("empty_block", "blocks/EmptyGridBlockBlue.png");
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
    app.start();

    
    return 0;
}