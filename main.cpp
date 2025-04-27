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
#include "CustomComponents/MainScene.h"
#include "Game/Tests/UITest/UIScene.h"
#include "Game/Tests/Physics/PhysicsScene.h"
#include "Game/Tests/PhysicsNodes/PhysicsTestScene.h"
#include "box2d/box2d.h"


int main() {
    Application app(sf::VideoMode(1600, 900), "LogisticHell");
    app.scene_system->registerScene(0, []() { return UIScene::create(10); });
//    app.set_new_scene(0);
    app.scene_system->registerScene(1, []() { return PhysicsScene::create(10); });
    app.scene_system->registerScene(2, []() { return PhysicsTestScene::create(10); });
    app.set_new_scene(2);
    app.start();


    return 0;
}