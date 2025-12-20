//
// Created by EgorRychkov on 19.07.2025.
//

#ifndef LOGISTICHELL_INSPECTOR_H
#define LOGISTICHELL_INSPECTOR_H


#include "../Base/Node.h"
#include "../Control/Controller.h"
#include "Button.h"
#include "../Render/Shapes/Text.h"

class InspectorController;


class Inspector : public Node {
public:
    static std::shared_ptr<Inspector>
    create(const std::shared_ptr<Node> &parent, EngineContext &ctx, const std::string &node_id,
           int render_priority = 0);

    explicit Inspector(const std::shared_ptr<Node> &parent, const std::string &node_id, int render_priority = 0)
            : Node(parent, node_id, render_priority) {}

    static void setup(std::shared_ptr<Inspector> &node, EngineContext &ctx);

    void set_inspector_visible(bool is_visible);

private:
    std::shared_ptr<InspectorController> controller;
    std::shared_ptr<Node> inspector_main_node;
    std::shared_ptr<UI::Button> background;
    std::shared_ptr<UI::Button> print_tree_bypass_button;
    std::shared_ptr<Text> print_tree_bypass_text;
    std::shared_ptr<UI::Button> print_sorted_tree_bypass_button;
    std::shared_ptr<Text> print_sorted_tree_bypass_text;
};


class InspectorController : public Controller {
private:
    std::weak_ptr<Inspector> inspector;
    bool is_inspector_active;
public:
    static std::shared_ptr<InspectorController>
    create(const std::shared_ptr<Node> &parent, const std::shared_ptr<Inspector> &inspector, const std::string &node_id,
           int render_priority = 0);

    explicit InspectorController(
        const std::shared_ptr<Node> &parent,
        const std::string &node_id,
        int render_priority = 0
    )
        : Controller(parent, node_id, render_priority)
    {}

    void on_key_release(sf::Event &event, EngineContext &ctx) override;
};


#endif //LOGISTICHELL_INSPECTOR_H
