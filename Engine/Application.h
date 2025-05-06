//
// Created by EgorRychkov on 10.04.2025.
//

#include "SFML/Graphics.hpp"
#include "EngineContext.h"
#include "Systems/SceneSystem.h"
#include "Systems/Tree.h"
#include "Systems/ControlSystem.h"
#include "Systems/UICollidersSystem.h"
#include "Systems/Atlas.h"

#ifndef LOGISTICHELL_APPLICATION_H
#define LOGISTICHELL_APPLICATION_H


class Application {
public:
    sf::VideoMode video_mode;
    std::string title;

    Application(const sf::VideoMode &videoMode, const std::string &title, int frame_limit);

    void start();

    void set_new_scene(int id);

    void set_loaded_scene(int id);

    void set_background_color(sf::Color new_color);

    std::shared_ptr<Scene> get_current_scene() const;

    SceneSystem *scene_system;

    ControlSystem *control_system;

    UICollidersSystem *ui_colliders_system;

    Tree *tree;

    sf::RenderWindow *window;

    sf::View standard_view;

    int frame_limit;

    sf::Color background_color = sf::Color::Black;

    Atlas *texture_atlas;

private:
    EngineContext ctx;
};


#endif //LOGISTICHELL_APPLICATION_H
