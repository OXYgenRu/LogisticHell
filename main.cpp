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

        node1 = ContainerNode::create(scene, 0);
        polygon = Polygon::create(node1);
        std::vector<sf::Vector2<float>> a = {{100, 100},
                                             {200, 100},
                                             {200, 200},
                                             {100, 200}};
        polygon->set_polygon(a);
        node2 = ContainerNode::create(scene, 1);
        polygon_1 = Polygon::create(node2);
        std::vector<sf::Vector2<float>> b = {{150, 100},
                                             {250, 100},
                                             {250, 200},
                                             {150, 200}};
        polygon_1->set_polygon(b);
        polygon_1->polygon.setFillColor(sf::Color::Yellow);
//        polygon->set_render_flag(false);
    }

    void update(EngineContext &ctx) override {
        polygon_1->polygon.setPoint(2,
                                    polygon_1->polygon.getPoint(2) +
                                    sf::Vector2f(30 * ctx.last_frame_delta_time, 30 * ctx.last_frame_delta_time));
//        polygon_1->polygon.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
    }

private:
    std::shared_ptr<ContainerNode> node1;
    std::shared_ptr<ContainerNode> node2;
    std::shared_ptr<Polygon> polygon;
    std::shared_ptr<Polygon> polygon_1;
};

int main() {
    Application app(sf::VideoMode(1600, 900), "LogisticHell");
    app.scene_system->registerScene(0, []() { return MainScene::create(10); });
    app.scene_system->set_new_scene(0);
    app.start();


    return 0;
}