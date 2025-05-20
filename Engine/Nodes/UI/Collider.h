//
// Created by EgorRychkov on 20.04.2025.
//

#ifndef LOGISTICHELL_COLLIDER_H
#define LOGISTICHELL_COLLIDER_H

#include "../Base/ContentNode.h"
#include "SFML/Graphics.hpp"
#include "Anchor.h"

namespace UI {
    class Collider : public ContentNode {
    public:
        static std::shared_ptr<Collider>
        create(std::shared_ptr<ContainerNode> parent, sf::Vector2f space_position, sf::Vector2f space_size,
               AnchorType anchor_type = AnchorType::Relative, AnchorBinding anchor_binding = AnchorBinding::LeftUp,
               int render_priority = 0);

        explicit Collider(std::shared_ptr<ContainerNode> parent, int render_priority = 0) : ContentNode(parent,
                                                                                                        render_priority) {}

        static void setup(std::shared_ptr<Collider> node, sf::Vector2f space_position,
                          sf::Vector2f space_size,
                          AnchorType anchor_type, AnchorBinding anchor_binding);

        void render(EngineContext &ctx) override;

        void update(EngineContext &ctx) override;

        int get_node_type() const override;

        void handle_mouse_press(sf::Event &event, EngineContext &ctx);

        void handle_mouse_release(sf::Event &event, EngineContext &ctx);

        void handle_mouse_move(sf::Event &event, EngineContext &ctx);

        void handle_mouse_enter(EngineContext &ctx);

        void handle_mouse_exit(EngineContext &ctx);

        void set_vertices(std::vector<sf::Vector2f> new_vertices);

        std::vector<sf::Vector2f> &get_vertices();

        void bind_on_mouse_press(const std::function<void(sf::Event &event, EngineContext &ctx)> &new_function);

        void bind_on_mouse_release(const std::function<void(sf::Event &event, EngineContext &ctx)> &new_function);

        void bind_on_mouse_moved(const std::function<void(sf::Event &event, EngineContext &ctx)> &new_function);

        void bind_on_mouse_enter(const std::function<void(EngineContext &ctx)> &new_function);

        void bind_on_mouse_exit(const std::function<void(EngineContext &ctx)> &new_function);

    private:
        std::vector<sf::Vector2f> vertices;
        Anchor anchor;
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


#endif //LOGISTICHELL_COLLIDER_H
