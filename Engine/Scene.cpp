//
// Created by EgorRychkov on 13.04.2025.
//

#include "Scene.h"

std::shared_ptr<Scene> Scene::create(const std::string &node_id) {
    auto node = std::make_shared<Scene>(node_id);
    return node;
}

int Scene::get_node_type() const {
    return 3;
}

void Scene::init_tree(EngineContext &ctx) {

}
