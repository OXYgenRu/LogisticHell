//
// Created by EgorRychkov on 09.08.2025.
//

#include "MouseApi.h"
#include "../../World/GameWorld.h"
#include "../../../../Engine/Application.h"

MouseApi::MouseApi(const std::shared_ptr<GameWorld> &world, EngineContext &ctx) : ctx(ctx) {
    this->world = world;
}

sf::Vector2f MouseApi::get_world_mouse_position() {
    sf::Vector2f pixelPos = ctx.app->window->mapPixelToCoords(sf::Mouse::getPosition(*ctx.app->window));
    sf::Vector2f localPos = world.lock()->get_cashed_recursive_transform().getInverse().transformPoint(
            pixelPos);
    return {localPos.x / world.lock()->get_pixel_per_meter(), -localPos.y / world.lock()->get_pixel_per_meter()};
}