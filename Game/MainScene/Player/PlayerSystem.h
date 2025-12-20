//
// Created by EgorRychkov on 10.11.2025.
//

#ifndef LOGISTICHELL_PLAYERSYSTEM_H
#define LOGISTICHELL_PLAYERSYSTEM_H


#include "../../../Engine/Nodes/Base/Node.h"
#include "Player.h"
#include <Optional>


class PlayerInputListeners {
private:
    std::optional<unsigned int> main_listener;
    std::optional<unsigned int> intercepting_listener;

    std::optional<unsigned int> background_main_listener;
    std::optional<unsigned int> background_intercepting_listener;

    unsigned int player_id;
public:
    explicit PlayerInputListeners(unsigned int player_id) : main_listener(std::nullopt),
                                                            intercepting_listener(std::nullopt),
                                                            background_main_listener(std::nullopt),
                                                            background_intercepting_listener(std::nullopt),
                                                            player_id(player_id) {}

    void set_main_listener(const unsigned int &id);

    void set_intercepting_listener(const unsigned int &id);

    void set_background_main_listener(const unsigned int &id);

    void set_background_intercepting_listener(const unsigned int &id);

    std::optional<unsigned int> get_main_listener();

    std::optional<unsigned int> get_intercepting_listener();

    std::optional<unsigned int> get_background_main_listener();

    std::optional<unsigned int> get_background_intercepting_listener();
};

class GameWorld;

class PlayerSystem : public Node {
private:
    unsigned int max_player_id{};
    std::unordered_map<unsigned int, std::shared_ptr<Player>> players;
    std::unordered_map<unsigned int, std::shared_ptr<PlayerInputListeners>> input_listeners;
    std::weak_ptr<GameWorld> world;
public:
    static std::shared_ptr<PlayerSystem>
    create(const std::shared_ptr<Node> &parent, const std::shared_ptr<GameWorld> &world,
           const std::string &node_id,
           int render_priority = 0);

    explicit PlayerSystem(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0)
            : Node(parent, node_id, render_priority) {};

    static void setup(const std::shared_ptr<PlayerSystem> &node, const std::shared_ptr<GameWorld> &world);

    std::shared_ptr<Player> create_player(const std::string &name);

    std::shared_ptr<PlayerInputListeners> get_player_listeners(const unsigned int &player_id);
};


#endif //LOGISTICHELL_PLAYERSYSTEM_H
