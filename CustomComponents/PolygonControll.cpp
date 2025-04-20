//
// Created by EgorRychkov on 17.04.2025.
//

#include "PolygonControll.h"
#include "MainScene.h"
#include "iostream"
#include "../Engine/Application.h"

std::shared_ptr<PolygonControll> PolygonControll::create(std::shared_ptr<ContainerNode> parent, int render_priority) {
    auto node = std::make_shared<PolygonControll>(parent, render_priority);
    parent->add_node(node);
    return node;
}


void PolygonControll::update(EngineContext &ctx) {
    auto to = ctx.app->get_current_scene();

}