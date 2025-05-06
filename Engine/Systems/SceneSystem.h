//
// Created by EgorRychkov on 13.04.2025.
//
#include "iostream"
#include "memory"
#include "functional"
#include "../Scene.h"
#include "../EngineContext.h"

#ifndef LOGISTICHELL_SCENESYSTEM_H
#define LOGISTICHELL_SCENESYSTEM_H


class SceneSystem {
public:
    using SceneFactory = std::function<std::shared_ptr<Scene>()>;

    void registerScene(int id, SceneFactory factory);

    void set_new_scene(int id, EngineContext &ctx);

    void set_loaded_scene(int id, EngineContext &ctx);

    void update_scene_selection(std::shared_ptr<ContainerNode> &scene, EngineContext &ctx);

    std::shared_ptr<Scene> currentScene;

private:
    std::unordered_map<int, SceneFactory> factories;
    std::unordered_map<int, std::shared_ptr<Scene>> loaded_scenes;
    bool need_to_set_new_scene = false;
    bool need_to_load_new_scene = false;
    int selected_scene_id;
};

#endif //LOGISTICHELL_SCENESYSTEM_H
