//
// Created by EgorRychkov on 13.04.2025.
//
#include "iostream"
#include "memory"
#include "functional"
#include "../Scene.h"

#ifndef LOGISTICHELL_SCENESYSTEM_H
#define LOGISTICHELL_SCENESYSTEM_H


class SceneSystem {
public:
    using SceneFactory = std::function<std::shared_ptr<Scene>()>;

    void registerScene(int id, SceneFactory factory);

    void set_new_scene(int id);

    void set_loaded_scene(int id);

    std::shared_ptr<Scene> currentScene;

private:
    std::unordered_map<int, SceneFactory> factories;
    std::unordered_map<int, std::shared_ptr<Scene>> loaded_scenes;

};

#endif //LOGISTICHELL_SCENESYSTEM_H
