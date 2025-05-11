//
// Created by EgorRychkov on 21.04.2025.
//

#ifndef LOGISTICHELL_UICOLLIDERSSYSTEM_H
#define LOGISTICHELL_UICOLLIDERSSYSTEM_H

#include "../EngineContext.h"
#include "SFML/Graphics.hpp"
#include "../Nodes/UI/UICollider.h"

class UICollidersSystem {
public:
    UICollidersSystem() = default;

    void update(EngineContext &ctx);

    void collect_event(sf::Event &event);

private:
    std::vector<sf::Event> control_events;
    std::shared_ptr<UICollider> last_used_collider;
};


#endif //LOGISTICHELL_UICOLLIDERSSYSTEM_H
