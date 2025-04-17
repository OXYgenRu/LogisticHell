//
// Created by EgorRychkov on 17.04.2025.
//

#ifndef LOGISTICHELL_CONTROLSYSTEM_H
#define LOGISTICHELL_CONTROLSYSTEM_H

#include "../EngineContext.h"
#include "SFML/Graphics.hpp"

class ControlSystem {
public:
    ControlSystem() = default;

    void update(EngineContext &ctx);

    void collect_event(sf::Event &event);

private:
    std::vector<sf::Event> control_events;
};


#endif //LOGISTICHELL_CONTROLSYSTEM_H
