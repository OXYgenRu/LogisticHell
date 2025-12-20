//
// Created by EgorRychkov on 14.12.2025.
//

#ifndef LOGISTICHELL_PLAYERSAPI_H
#define LOGISTICHELL_PLAYERSAPI_H


#include "SFML/Graphics.hpp"
#include "memory"

class GameWorld;

class PlayersApi {
private:
    std::weak_ptr<GameWorld> world;
public:
    explicit PlayersApi(const std::shared_ptr<GameWorld> &world);

    unsigned int create_player(const std::string &name);

    void set_main_listener(const unsigned int &player_id, const unsigned int &listener_id);
};


#endif //LOGISTICHELL_PLAYERSAPI_H
