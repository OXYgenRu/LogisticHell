//
// Created by EgorRychkov on 07.04.2025.
//
#include "iostream"
#include "Engine/Application.h"
#include "Engine/Nodes/Base/Node.h"
#include "Engine/Nodes/Base/ContainerNode.h"
#include "Engine/Nodes/Base/ContentNode.h"
#include "Engine/Scene.h"

class MainScene : public Scene {
public:
    MainScene() : Scene() {}

    void init_tree() override {
        auto scene = shared_from_this();
        auto node1 = ContentNode::create(scene);
        auto node2 = ContentNode::create(scene);
//    std::cout << scene->container_nodes.size();
        auto node1_1 = ContainerNode::create(scene);
        auto node1_2 = ContentNode::create(node1_1);
        auto node1_3 = ContentNode::create(node1_1);
    }
};

int main() {
    Application app(sf::VideoMode(1600, 900), "LogisticHell");
    app.scene_system->registerScene(0, []() { return std::make_shared<MainScene>(); });
    app.scene_system->set_new_scene(0);
    app.start();


    return 0;
}