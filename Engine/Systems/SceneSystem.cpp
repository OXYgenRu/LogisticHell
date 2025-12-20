//
// Created by EgorRychkov on 13.04.2025.
//

#include "SceneSystem.h"
#include "../Application.h"

void SceneSystem::registerScene(int id, SceneFactory factory) { // TODO const and const&
    factories[id] = factory;
}

void SceneSystem::set_new_scene(int id, EngineContext &ctx) {
    auto it = factories.find(id);
    if (it == factories.end()) {
        std::cout << "TestScene ID " << id << " not found\n";
        return;
    }
    this->need_to_set_new_scene = true;
    this->selected_scene_id = id;
}

void SceneSystem::set_loaded_scene(int id, EngineContext &ctx) {
    auto it = loaded_scenes.find(id);
    if (it != loaded_scenes.end()) {
        need_to_load_new_scene = true;
        selected_scene_id = id;
    } else {
        std::cout << "TestScene ID " << id << " not found\n";
    }
}

void SceneSystem::update_scene_selection(std::shared_ptr<Node> &scene, EngineContext &ctx) {
    if (need_to_load_new_scene) {
        currentScene = loaded_scenes[selected_scene_id];
        need_to_load_new_scene = false;
        return;
    }
    if (need_to_set_new_scene) {
        auto it = factories.find(selected_scene_id);
        currentScene = it->second();
        currentScene->init_tree(ctx);
        loaded_scenes[selected_scene_id] = currentScene;
        scene = std::static_pointer_cast<Node>(currentScene);
        need_to_set_new_scene = false;
        return;
    }
}