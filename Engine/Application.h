//
// Created by EgorRychkov on 10.04.2025.
//

#include "SFML/Graphics.hpp"
#include "EngineContext.h"

#ifndef LOGISTICHELL_APPLICATION_H
#define LOGISTICHELL_APPLICATION_H


class Application {
public:
    sf::VideoMode video_mode;
    std::string title;

    Application(const sf::VideoMode &videoMode, const std::string &title);

    void start();

private:
    sf::RenderWindow *window;
    EngineContext ctx;
};


#endif //LOGISTICHELL_APPLICATION_H
