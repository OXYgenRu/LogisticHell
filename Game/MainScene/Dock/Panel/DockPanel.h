//
// Created by EgorRychkov on 01.05.2025.
//

#ifndef LOGISTICHELL_DOCKPANEL_H
#define LOGISTICHELL_DOCKPANEL_H


#include "../../../../Engine/Nodes/Base/ContainerNode.h"
#include "../Dock.h"

class DockPanel : public ContainerNode {
public:
    static std::shared_ptr<DockPanel>
    create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<Dock> dock,
           int render_priority = 0,
           int render_priority_layers = 10);


    explicit DockPanel(std::shared_ptr<ContainerNode> parent, int render_priority = 0) : ContainerNode(parent,
                                                                                                       render_priority) {}

    static void setup(std::shared_ptr<DockPanel> node, std::shared_ptr<Dock> dock);

    void update(EngineContext &ctx) override;

    std::weak_ptr<Dock> dock;
    std::shared_ptr<Polygon> polygon;
    std::shared_ptr<Text> text;
    std::shared_ptr<UICollider> background_collider;
    std::shared_ptr<Text> selected_unit;
};


#endif //LOGISTICHELL_DOCKPANEL_H
