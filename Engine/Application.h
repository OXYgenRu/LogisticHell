//
// Created by EgorRychkov on 10.04.2025.
//

#include "SFML/Graphics.hpp"
#include "EngineContext.h"
#include "Systems/SceneSystem.h"
#include "Systems/Tree.h"
#include "Systems/ControlSystem.h"

#ifndef LOGISTICHELL_APPLICATION_H
#define LOGISTICHELL_APPLICATION_H


class Application {
public:
    sf::VideoMode video_mode;
    std::string title;

    Application(const sf::VideoMode &videoMode, const std::string &title);

    void start();

    void set_new_scene(int id);

    void set_loaded_scene(int id);

    std::shared_ptr<Scene> get_current_scene() const;

    SceneSystem *scene_system;

    ControlSystem *control_system;

    Tree *tree;

    sf::RenderWindow *window;

    sf::View standard_view;
private:
    EngineContext ctx;
};


#endif //LOGISTICHELL_APPLICATION_H
