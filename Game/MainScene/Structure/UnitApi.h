//
// Created by EgorRychkov on 01.07.2025.
//

#ifndef LOGISTICHELL_UNITAPI_H
#define LOGISTICHELL_UNITAPI_H

#include "memory"
#include "SFML/Graphics.hpp"
#include "../../../Engine/EngineContext.h"

class Unit;

class UnitApi;

class UnitBehavior {
public:
    virtual void update(EngineContext &ctx, UnitApi &api) {}

    virtual void on_key_press(sf::Event &event, EngineContext &ctx, UnitApi &api) {}

    virtual void on_key_release(sf::Event &event, EngineContext &ctx, UnitApi &api) {}
};

class UnitApi {
public:
    UnitApi(const std::shared_ptr<Unit> &unit);

    UnitApi();

    void
    apply_force(const sf::Vector2i &block_position, const sf::Vector2f &relative_position, const sf::Vector2f &force);

private:
    std::weak_ptr<Unit> weak_unit;
};


#endif //LOGISTICHELL_UNITAPI_H
