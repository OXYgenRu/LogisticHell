//
// Created by EgorRychkov on 13.04.2025.
//

#include "Scene.h"

std::shared_ptr<Scene> Scene::create(int render_priority_layers) {
    auto node = std::make_shared<Scene>();
    return node;
}

int Scene::get_node_type() const {
    return 3;
}

void Scene::init_tree(EngineContext &ctx) {

}
