//
// Created by EgorRychkov on 10.04.2025.
//

#include "Application.h"
#include "EngineContext.h"
#include "Systems/UICollidersSystem.h"

Application::Application(const sf::VideoMode &videoMode, const std::string &title) {
    this->ctx = EngineContext();
    this->ctx.app = this;
    this->video_mode = videoMode;
    this->title = title;
    this->window = nullptr;
    this->tree = new Tree();
    this->scene_system = new SceneSystem();
    this->control_system = new ControlSystem();
    this->ui_colliders_system = new UICollidersSystem();
    this->standard_view = sf::View(sf::Vector2f(float(videoMode.width) / 2, float(videoMode.height) / 2),
                                   sf::Vector2f(float(videoMode.width), float(videoMode.height)));
}

void Application::start() {
    this->window = new sf::RenderWindow(this->video_mode, this->title);
    sf::Clock clock;
    sf::Event event{};
    std::shared_ptr<ContainerNode> scene = this->scene_system->currentScene;

    while (this->window->isOpen()) {
        float delta_time = clock.restart().asSeconds();
        ctx.last_frame_delta_time = delta_time;

        this->tree->drop_tree();
//        scene = this->scene_system->currentScene;
        this->tree->traverse(scene, ctx);
        this->tree->update_view_tracker(ctx);

        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            this->control_system->collect_event(event);
            this->ui_colliders_system->collect_event(event);
        }
        this->control_system->update(this->ctx);
        this->ui_colliders_system->update(this->ctx);

        this->tree->update(this->ctx);

        window->clear();
        this->tree->render(this->ctx);
        window->display();
    }
}

void Application::set_new_scene(int id) {
    this->scene_system->set_new_scene(id, this->ctx);
    auto to = std::static_pointer_cast<ContainerNode>(this->scene_system->currentScene);
    this->tree->print_tree(to);
}

void Application::set_loaded_scene(int id) {
    this->scene_system->set_loaded_scene(id, this->ctx);
}

std::shared_ptr<Scene> Application::get_current_scene() const {
    return this->scene_system->currentScene;
}