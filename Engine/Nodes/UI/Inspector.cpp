//
// Created by EgorRychkov on 19.07.2025.
//

#include "Inspector.h"
#include "../../../Engine/Application.h"

std::shared_ptr<Inspector>
Inspector::create(const std::shared_ptr<Node> &parent, EngineContext &ctx, const std::string &node_id,
                  int render_priority) {
    auto node = std::make_shared<Inspector>(parent, node_id, render_priority);
    Inspector::setup(node, ctx);
    parent->add_node(node);
    return node;
}


void Inspector::setup(std::shared_ptr<Inspector> &node, EngineContext &ctx) {
    node->controller = InspectorController::create(node, node, "InspectorController");
    node->inspector_main_node = Node::create(node, "InspectorMainNode");

    node->background = UI::Button::create(node->inspector_main_node, ctx, "InspectorBackground");
    node->background->set_rectangle({0, 0}, {300, 180});
    node->background->set_color(sf::Color(36, 36, 36));

    node->print_tree_bypass_button = UI::Button::create(node->inspector_main_node, ctx, "PrintTreeBypassButton", 1);
    node->print_tree_bypass_button->set_rectangle({0, 0}, {60, 60});
    node->print_tree_bypass_button->set_position({10, 10});
    node->print_tree_bypass_button->set_color(sf::Color(63, 72, 204));
    node->print_tree_bypass_button->set_hold_reaction(true);
    node->print_tree_bypass_button->bind_on_mouse_release([](sf::Event &event, EngineContext &ctx) {
        std::vector<BypassUnit> bypass = ctx.app->tree->get_tree_bypass(ctx);
        for (auto &to: bypass) {
            for (int i = 0; i < to.history.size(); i++) {
                std::cout << "-";
            }
            std::cout << to.node->get_node_id() << '\n';
        }
    });

    node->print_tree_bypass_text = Text::create(node->print_tree_bypass_button, "PrintTreeBypassText", 1);
    node->print_tree_bypass_text->set_position({80, 20});
    node->print_tree_bypass_text->set_text("Print bypass");
    node->print_tree_bypass_text->set_character_size(48);
    node->print_tree_bypass_text->set_scale(0.25);
    node->print_tree_bypass_text->set_color(sf::Color(255, 255, 255));
    node->print_tree_bypass_text->set_smooth(true);

    node->print_sorted_tree_bypass_button = UI::Button::create(node->inspector_main_node, ctx,
                                                               "PrintSortedTreeBypassButton", 1);
    node->print_sorted_tree_bypass_button->set_rectangle({0, 0}, {60, 60});
    node->print_sorted_tree_bypass_button->set_position({10, 100});
    node->print_sorted_tree_bypass_button->set_color(sf::Color(63, 72, 204));
    node->print_sorted_tree_bypass_button->set_hold_reaction(true);
    node->print_sorted_tree_bypass_button->bind_on_mouse_release([](sf::Event &event, EngineContext &ctx) {
        std::vector<BypassUnit> bypass = ctx.app->tree->get_sorted_tree_bypass(ctx);
        int max_history_size = 0;
        for (auto &to: bypass) {
            int history_size = 0;
            for (auto &x: to.history) {
                history_size += int(x.size()) + 1;
            }
            max_history_size = std::max(max_history_size, history_size);
        }
        for (auto &to: bypass) {
            int history_size = 0;
            for (auto &x: to.history) {
                history_size += int(x.size()) + 1;
            }
            std::cout << '[';
            for (auto &x: to.history) {
                std::cout << x << '/';
            }
            for (int i = 0; i < max_history_size - history_size; i++) {
                std::cout << ' ';
            }
            std::cout << "] " << to.global_render_priority << ' ' << to.node->get_node_id() << '\n';
        }

    });

    node->print_tree_bypass_text = Text::create(node->print_sorted_tree_bypass_button, "PrintSortedTreeBypassText", 1);
    node->print_tree_bypass_text->set_position({80, 20});
    node->print_tree_bypass_text->set_text("Print sorted bypass");
    node->print_tree_bypass_text->set_character_size(48);
    node->print_tree_bypass_text->set_scale(0.25);
    node->print_tree_bypass_text->set_color(sf::Color(255, 255, 255));
    node->print_tree_bypass_text->set_smooth(true);

    node->inspector_main_node->set_render_flag(false);
    node->inspector_main_node->set_update_flag(false);
}

void Inspector::set_inspector_visible(bool is_visible) {
    this->inspector_main_node->set_render_flag(is_visible);
    this->inspector_main_node->set_update_flag(is_visible);
}

std::shared_ptr<InspectorController>
InspectorController::create(const std::shared_ptr<Node> &parent, const std::shared_ptr<Inspector> &inspector,
                            const std::string &node_id,
                            int render_priority) {
    auto node = std::make_shared<InspectorController>(parent, node_id, render_priority);
    node->inspector = inspector;
    node->is_inspector_active = false;
    parent->add_node(node);
    return node;
}

void InspectorController::on_key_release(sf::Event &event, EngineContext &ctx) {
    if (event.key.code == sf::Keyboard::Key::Tilde) {
        is_inspector_active = !is_inspector_active;
        inspector.lock()->set_inspector_visible(is_inspector_active);
    }

}