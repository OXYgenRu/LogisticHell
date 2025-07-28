//
// Created by EgorRychkov on 01.05.2025.
//

#ifndef LOGISTICHELL_EDITORINTERFACE_H
#define LOGISTICHELL_EDITORINTERFACE_H


#include "../../../../Engine/Nodes/Base/Node.h"
#include "../../../../Engine/Nodes/UI/Button.h"
#include "../../../../Engine/Nodes/Render/Shapes/Text.h"
#include "../../../../Engine/Nodes/UI/Rectangle.h"
#include "../../../../Engine/Nodes/UI/VerticalList.h"
#include "BlocksInventory.h"

class Dock;

class EditorInterface : public Node {
public:
    static std::shared_ptr<EditorInterface>
    create(const std::shared_ptr<Node> &parent, EngineContext &ctx, const std::shared_ptr<Dock> &dock,
           const std::shared_ptr<GameWorld> &world, const std::string &node_id,
           int render_priority = 0);


    explicit EditorInterface(const std::shared_ptr<Node> &parent, const std::string &node_id,
                             int render_priority = 0) : Node(parent, node_id,
                                                             render_priority) {}

    static void
    setup(const std::shared_ptr<EditorInterface> &node, EngineContext &ctx, const std::shared_ptr<Dock> &dock,
          const std::shared_ptr<GameWorld> &world);

    void update(EngineContext &ctx) override;

    std::weak_ptr<Dock> dock;
    std::shared_ptr<Node> buttons_layer;
    std::shared_ptr<UI::Button> buttons_layer_background;
    std::shared_ptr<UI::Button> attachment_mode;
    std::shared_ptr<UI::Button> destroying_mode;
    std::shared_ptr<UI::Button> assemble_blueprint;
    std::shared_ptr<UI::Button> quit_dock;
    std::shared_ptr<BlocksInventory> inventory;
};


#endif //LOGISTICHELL_EDITORINTERFACE_H
