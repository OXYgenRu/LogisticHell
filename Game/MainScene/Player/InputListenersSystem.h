//
// Created by EgorRychkov on 10.11.2025.
//

#ifndef LOGISTICHELL_INPUTLISTENERSSYSTEM_H
#define LOGISTICHELL_INPUTLISTENERSSYSTEM_H

#include <SFML/Graphics.hpp>
#include "../../../Engine/Nodes/Base/Node.h"
#include "../../../Engine/Nodes/Control/Controller.h"
#include <optional>

class Api;

class InputListener {
private:
    std::vector<unsigned int> listener_observers;
    unsigned int listener_id;
public:
    void add_observer(const unsigned int &observer_id);

    void delete_observer(const unsigned int &observer_id);

    const std::vector<unsigned int> &get_observers();

    virtual void on_key_press(const unsigned int &observer, const sf::Keyboard::Key &key, Api &api) {}

    virtual void on_key_release(const unsigned int &observer, const sf::Keyboard::Key &key, Api &api) {}

    virtual void while_key_pressed(const unsigned int &observer, const sf::Keyboard::Key &key, Api &api) {}
};

class GameWorld;


class InputListenersSystem : public Node {
private:
    unsigned int max_listener_id{};
    std::unordered_map<unsigned int, std::shared_ptr<InputListener>> input_listeners;
    std::weak_ptr<GameWorld> world;
public:
    static std::shared_ptr<InputListenersSystem>
    create(const std::shared_ptr<Node> &parent, const std::shared_ptr<GameWorld> &world,
           const std::string &node_id,
           int render_priority = 0);

    explicit InputListenersSystem(const std::shared_ptr<Node> &parent, const std::string &node_id,
                                  int render_priority = 0)
            : Node(parent, node_id, render_priority) {};

    static void setup(const std::shared_ptr<InputListenersSystem> &node, const std::shared_ptr<GameWorld> &world);

    unsigned int register_listener(const std::shared_ptr<InputListener> &listener);

    std::shared_ptr<InputListener> get_listener(const std::optional<unsigned int> &id);

    void on_key_press(const std::shared_ptr<InputListener> &listener, const sf::Keyboard::Key &key);

    void on_key_release(const std::shared_ptr<InputListener> &listener, const sf::Keyboard::Key &key);

    void while_key_pressed(const std::shared_ptr<InputListener> &listener, const sf::Keyboard::Key &key);
};


#endif //LOGISTICHELL_INPUTLISTENERSSYSTEM_H
