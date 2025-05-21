//
// Created by EgorRychkov on 18.05.2025.
//

#ifndef LOGISTICHELL_BUTTON_H
#define LOGISTICHELL_BUTTON_H

#include "memory"
#include "../Base/ContainerNode.h"
#include "Collider.h"
#include "Rectangle.h"
#include "functional"

namespace UI {
    class Button : public ContainerNode {
    public:
        static std::shared_ptr<Button>
        create(std::shared_ptr<ContainerNode> parent, EngineContext &ctx,
               sf::Vector2f space_size,
               AnchorType anchor_type = AnchorType::Relative, AnchorBinding anchor_binding = AnchorBinding::LeftUp,
               int render_priority = 0,
               int render_priority_layers = 10
        );


        explicit Button(std::shared_ptr<ContainerNode> parent, int render_priority = 0)
                : ContainerNode(parent, render_priority) {}

        static void setup(std::shared_ptr<Button> &node, EngineContext &ctx, sf::Vector2f &space_position,
                          AnchorType &anchor_type, AnchorBinding &anchor_binding);

        void set_rectangle(sf::Vector2f new_top_left, sf::Vector2f new_bottom_right);

        void set_texture(const std::string &new_texture_name, EngineContext &ctx);

        void set_color(sf::Color color);

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


        std::shared_ptr<UI::Rectangle> rectangle;
        std::shared_ptr<UI::Collider> collider;

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
