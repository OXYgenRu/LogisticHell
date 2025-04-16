//
// Created by EgorRychkov on 10.04.2025.
//

#include "Application.h"
#include "EngineContext.h"

Application::Application(const sf::VideoMode &videoMode, const std::string &title) {
    this->ctx = EngineContext();
    this->ctx.app = this;
    this->video_mode = videoMode;
    this->title = title;
    this->window = nullptr;
    this->tree = new Tree();
    this->scene_system = new SceneSystem();
}

void Application::start() {
    this->window = new sf::RenderWindow(this->video_mode, this->title);
    sf::Clock clock;
    sf::Event event{};
    std::shared_ptr<ContainerNode> scene = this->scene_system->currentScene;

    while (this->window->isOpen()) {
        float delta_time = clock.restart().asSeconds();

        this->tree->drop_tree();
        scene = this->scene_system->currentScene;
        this->tree->traverse(scene);

        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }

        window->clear();
        this->tree->render(this->ctx);
        window->display();
    }
}