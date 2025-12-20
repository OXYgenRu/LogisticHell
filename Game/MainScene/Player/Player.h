//
// Created by EgorRychkov on 10.11.2025.
//

#ifndef LOGISTICHELL_PLAYER_H
#define LOGISTICHELL_PLAYER_H


#include "../../../Engine/Nodes/Base/Node.h"
#include "../../../Engine/Nodes/Control/Controller.h"

class GameWorld;

class PlayerInput : public Controller {
private:
    unsigned int player_id;
    std::weak_ptr<GameWorld> world;
    sf::Keyboard::Key last_key;
public:
    static std::shared_ptr<PlayerInput>
    create(const std::shared_ptr<Node> &parent, const unsigned int &player_id, const std::shared_ptr<GameWorld> &world,
           const std::string &node_id, int render_priority = 0);

    explicit PlayerInput(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0)
            : Controller(parent, node_id, render_priority) {}

    static void
    setup(const std::shared_ptr<PlayerInput> &node, const unsigned int &player_id,
          const std::shared_ptr<GameWorld> &world);

    void on_key_press(sf::Event &event, EngineContext &ctx) override;

    void on_key_release(sf::Event &event, EngineContext &ctx) override;

    void update(EngineContext &ctx) override;
};

class Player : public Node {
private:
    unsigned int player_id;
    std::shared_ptr<Controller> player_input;
    std::weak_ptr<GameWorld> world;
public:
    static std::shared_ptr<Player>
    create(const std::shared_ptr<Node> &parent, const unsigned int &player_id, const std::shared_ptr<GameWorld> &world,
           const std::string &node_id,
           int render_priority = 0);

    explicit Player(const std::shared_ptr<Node> &parent, const std::string &node_id,
                    int render_priority = 0)
            : Node(parent, node_id, render_priority) {};

    static void
    setup(const std::shared_ptr<Player> &node, const unsigned int &player_id, const std::shared_ptr<GameWorld> &world);

    const unsigned int &get_id();
};


#endif //LOGISTICHELL_PLAYER_H
