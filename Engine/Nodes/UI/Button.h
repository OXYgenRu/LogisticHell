//
// Created by EgorRychkov on 18.05.2025.
//

#ifndef LOGISTICHELL_BUTTON_H
#define LOGISTICHELL_BUTTON_H

#include "memory"
#include "../Base/Node.h"
#include "Collider.h"
#include "Rectangle.h"
#include "functional"

namespace UI {
    class Button : public Node {
    public:
        static std::shared_ptr<Button>
        create(const std::shared_ptr<Node> &parent, EngineContext &ctx,
               int render_priority = 0);

        explicit Button(const std::shared_ptr<Node> &parent, int render_priority = 0)
                : Node(parent, render_priority) {}

        static void setup(std::shared_ptr<Button> &node, EngineContext &ctx);

        void set_rectangle(sf::Vector2f new_top_left, sf::Vector2f new_bottom_right);

        void set_texture(const std::string &new_texture_name, EngineContext &ctx);

        void set_color(const sf::Color &color);

        void set_hold_reaction(bool is_react_to_hold);

        void bind_on_mouse_press(const std::function<void(sf::Event &event, EngineContext &ctx)> &new_function);

        void bind_on_mouse_release(const std::function<void(sf::Event &event, EngineContext &ctx)> &new_function);

        void bind_on_mouse_moved(const std::function<void(sf::Event &event, EngineContext &ctx)> &new_function);

        void bind_on_mouse_enter(const std::function<void(EngineContext &ctx)> &new_function);

        void bind_on_mouse_exit(const std::function<void(EngineContext &ctx)> &new_function);

    private:
        void handle_on_mouse_press(sf::Event &event, EngineContext &ctx);

        void handle_on_mouse_release(sf::Event &event, EngineContext &ctx);

        void handle_on_mouse_move(sf::Event &event, EngineContext &ctx);

        void handle_on_mouse_enter(EngineContext &ctx);

        void handle_on_mouse_exit(EngineContext &ctx);

        bool is_pressed;
        bool react_to_hold;
        std::shared_ptr<UI::Rectangle> rectangle;
        std::shared_ptr<UI::Collider> collider;
        sf::Color color;

        std::function<void(sf::Event &event, EngineContext &ctx)> on_mouse_press = [](sf::Event &event,
                                                                                      EngineContext &ctx) {};
        std::function<void(sf::Event &event, EngineContext &ctx)> on_mouse_release = [](sf::Event &event,
                                                                                        EngineContext &ctx) {};
        std::function<void(sf::Event &event, EngineContext &ctx)> on_mouse_moved = [](sf::Event &event,
                                                                                      EngineContext &ctx) {};
        std::function<void(EngineContext &ctx)> on_mouse_enter = [](EngineContext &ctx) {};
        std::function<void(EngineContext &ctx)> on_mouse_exit = [](EngineContext &ctx) {};
    };

}


#endif //LOGISTICHELL_BUTTON_H
