//
// Created by EgorRychkov on 13.04.2025.
//

#include "SceneSystem.h"

void SceneSystem::registerScene(int id, SceneFactory factory) {
    factories[id] = factory;
}

void SceneSystem::set_new_scene(int id) {
    auto it = factories.find(id);
    if (it != factories.end()) {
        currentScene = it->second();
        loaded_scenes[id] = currentScene;
    } else {
        std::cout << "Scene ID " << id << " not found\n";
    }
}

void SceneSystem::set_loaded_scene(int id) {
    auto it = loaded_scenes.find(id);
    if (it != loaded_scenes.end()) {
        currentScene = loaded_scenes[id];
    } else {
        std::cout << "Scene ID " << id << " not found\n";
    }
}

