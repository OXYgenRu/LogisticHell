//
// Created by EgorRychkov on 10.04.2025.
//

#include "Application.h"
#include "EngineContext.h"
#include "Systems/UICollidersSystem.h"

Application::Application(const sf::VideoMode &videoMode, const std::string &title, int frame_limit) {
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
    this->frame_limit = frame_limit;
    this->texture_atlas = new Atlas(sf::Vector2i(256, 256));
    this->batch = new Batch();
}

void Application::start() {
    std::cerr.tie(&std::cout);
    this->window = new sf::RenderWindow(this->video_mode, this->title, sf::Style::Titlebar | sf::Style::Close);
    this->window->setVerticalSyncEnabled(true);
    sf::Clock clock;
    sf::Event event{};
    std::shared_ptr<Node> scene = this->scene_system->currentScene;
    this->window->setFramerateLimit(this->frame_limit);
    this->window->setKeyRepeatEnabled(false);
    this->texture_atlas->build();
    this->batch->set_texture(*this->texture_atlas->get_texture(), ctx);
    sf::Transform scene_transform;
    scene_transform.translate(this->get_window_size().x / 2, this->get_window_size().y / 2);
    try {
        while (this->window->isOpen()) {
            float delta_time = clock.restart().asSeconds();
            ctx.last_frame_delta_time = delta_time;

            this->scene_system->update_scene_selection(scene, ctx);

            this->tree->drop_tree();

            this->tree->traverse(scene, ctx, scene_transform, 0);

            this->tree->prepare_tree();

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

            window->clear(this->background_color);
            this->tree->render(this->ctx);
            window->display();
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Application::set_new_scene(int id) {
    this->scene_system->set_new_scene(id, this->ctx);
}

void Application::set_loaded_scene(int id) {
    this->scene_system->set_loaded_scene(id, this->ctx);
}

std::shared_ptr<Scene> Application::get_current_scene() const {
    return this->scene_system->currentScene;
}

void Application::set_background_color(sf::Color new_color) {
    this->background_color = new_color;
}

sf::Vector2f Application::get_window_size() const {
    return {float(this->window->getSize().x), float(this->window->getSize().y)};
}