//
// Created by EgorRychkov on 01.05.2025.
//

#ifndef LOGISTICHELL_EDITORINTERFACE_H
#define LOGISTICHELL_EDITORINTERFACE_H


#include "../../../../Engine/Nodes/Base/ContainerNode.h"
#include "../../../../Engine/Nodes/UI/UIPolygon.h"
#include "../../../../Engine/Nodes/UI/Button.h"
#include "../../../../Engine/Nodes/Render/Shapes/Text.h"
#include "../../../../Engine/Nodes/UI/Rectangle.h"

class Dock;

class EditorInterface : public ContainerNode {
public:
    static std::shared_ptr<EditorInterface>
    create(std::shared_ptr<ContainerNode> parent, EngineContext &ctx, std::shared_ptr<Dock> dock,
           int render_priority = 0,
           int render_priority_layers = 10);


    explicit EditorInterface(std::shared_ptr<ContainerNode> parent, int render_priority = 0) : ContainerNode(parent,
                                                                                                             render_priority) {}

    static void setup(std::shared_ptr<EditorInterface> node, EngineContext &ctx, std::shared_ptr<Dock> dock);

    void update(EngineContext &ctx) override;

    std::weak_ptr<Dock> dock;
    std::shared_ptr<UI::Rectangle> background;
    std::shared_ptr<Text> text;
    std::shared_ptr<UI::Collider> background_collider;
    std::shared_ptr<UI::Button> attachment_mode;
    std::shared_ptr<UI::Button> destroying_mode;
    std::shared_ptr<Text> selected_unit;
};


#endif //LOGISTICHELL_EDITORINTERFACE_H
