//
// Created by EgorRychkov on 21.11.2025.
//

#ifndef LOGISTICHELL_LISTENERSAPI_H
#define LOGISTICHELL_LISTENERSAPI_H

#include "SFML/Graphics.hpp"
#include "memory"

#include "../../Player/InputListenersSystem.h"

class ListenersApi {
private:
    std::weak_ptr<GameWorld> world;
public:
    explicit ListenersApi(const std::shared_ptr<GameWorld> &world);

    unsigned int register_listener(const std::shared_ptr<InputListener> &listener);

    void add_observer(const unsigned int &listener_id, const unsigned int &observer_id);

    void delete_observer(const unsigned int &listener_id, const unsigned int &observer_id);
};


#endif //LOGISTICHELL_LISTENERSAPI_H
