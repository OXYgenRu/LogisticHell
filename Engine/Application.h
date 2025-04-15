//
// Created by EgorRychkov on 10.04.2025.
//

#include "SFML/Graphics.hpp"
#include "EngineContext.h"
#include "Systems/SceneSystem.h"
#include "Systems/Tree.h"

#ifndef LOGISTICHELL_APPLICATION_H
#define LOGISTICHELL_APPLICATION_H


class Application {
public:
    sf::VideoMode video_mode;
    std::string title;

    Application(const sf::VideoMode &videoMode, const std::string &title);

    void start();

    SceneSystem *scene_system;

    Tree *tree;
private:
    sf::RenderWindow *window;
    EngineContext *ctx;
};


#endif //LOGISTICHELL_APPLICATION_H
