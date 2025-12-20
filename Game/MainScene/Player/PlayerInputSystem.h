//
// Created by EgorRychkov on 10.11.2025.
//

#ifndef LOGISTICHELL_PLAYERINPUTSYSTEM_H
#define LOGISTICHELL_PLAYERINPUTSYSTEM_H


#include "../../../Engine/Nodes/Base/Node.h"
#include "optional"

class GameWorld;

class InputListener;

class PlayerInputSystem : public Node {
private:
    std::weak_ptr<GameWorld> world;

    std::pair<
            std::optional<std::shared_ptr<InputListener>>,
            std::optional<std::shared_ptr<InputListener>>>
    get_player_listeners(const unsigned int &player_id);

public:
    static std::shared_ptr<PlayerInputSystem>
    create(const std::shared_ptr<Node> &parent, const std::shared_ptr<GameWorld> &world,
           const std::string &node_id,
           int render_priority = 0);

    explicit PlayerInputSystem(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0)
            : Node(parent, node_id, render_priority) {};

    static void setup(const std::shared_ptr<PlayerInputSystem> &node, const std::shared_ptr<GameWorld> &world);

    void handle_key_press(const unsigned int &player_id, const sf::Keyboard::Key &key);

    void handle_key_release(const unsigned int &player_id, const sf::Keyboard::Key &key);

    void handle_while_key_pressed(const unsigned int &player_id, const sf::Keyboard::Key &key);
};


#endif //LOGISTICHELL_PLAYERINPUTSYSTEM_H
