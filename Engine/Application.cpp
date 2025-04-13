//
// Created by EgorRychkov on 10.04.2025.
//

#include "Application.h"
#include "EngineContext.h"

Application::Application(const sf::VideoMode &videoMode, const std::string &title) {
    this->ctx = new EngineContext();
    this->ctx->app = this;
    this->video_mode = videoMode;
    this->title = title;
    this->window = nullptr;
}

void Application::start() {
    this->window = new sf::RenderWindow(this->video_mode, this->title);
    sf::Clock clock;
    sf::Event event{};
    while (this->window->isOpen()) {
        float delta_time = clock.restart().asSeconds();

        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }
        window->clear();
        window->display();
    }
}