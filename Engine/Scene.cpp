//
// Created by EgorRychkov on 13.04.2025.
//

#include "Scene.h"

std::shared_ptr<Scene> Scene::create(int render_priority_layers) {
    auto node = std::make_shared<Scene>();
    node->set_render_layers_count(render_priority_layers + 1);
    return node;
}

int Scene::get_node_type() const {
    return 3;
}

void Scene::init_tree(EngineContext &ctx) {

}