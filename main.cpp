//
// Created by EgorRychkov on 07.04.2025.
//
#include "iostream"
#include "Engine/Application.h"
#include "Engine/Nodes/Base/Node.h"
#include "Engine/Nodes/Base/ContainerNode.h"
#include "Engine/Nodes/Base/ContentNode.h"
#include "Engine/Scene.h"
#include "Engine/Nodes/Render/Shapes/Polygon.h"

class MainScene : public Scene {
public:
    static std::shared_ptr<MainScene> create(int render_priority_layers) {
        auto node = std::make_shared<MainScene>();
        node->set_render_layers_count(render_priority_layers + 1);
        return node;
    }

    MainScene() : Scene() {}

    void init_tree() override {
        auto scene = shared_from_this();

        auto node1 = ContainerNode::create(scene, 0);
        auto polygon = Polygon::create(node1);
        std::vector<sf::Vector2<float>> a = {{100, 100},
                                             {200, 100},
                                             {200, 200},
                                             {100, 200}};
        polygon->set_polygon(a);
        auto node2 = ContainerNode::create(scene, 1);
        auto polygon_1 = Polygon::create(node2);
        std::vector<sf::Vector2<float>> b = {{150, 100},
                                             {250, 100},
                                             {250, 200},
                                             {150, 200}};
        polygon_1->set_polygon(b);
        polygon_1->polygon.setFillColor(sf::Color::Yellow);
        polygon->set_render_flag(false);
    }
};

int main() {
    Application app(sf::VideoMode(1600, 900), "LogisticHell");
    app.scene_system->registerScene(0, []() { return MainScene::create(10); });
    app.scene_system->set_new_scene(0);
    app.start();


    return 0;
}