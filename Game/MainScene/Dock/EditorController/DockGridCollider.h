//
// Created by EgorRychkov on 01.05.2025.
//

#ifndef LOGISTICHELL_DOCKGRIDCOLLIDER_H
#define LOGISTICHELL_DOCKGRIDCOLLIDER_H


#include "../../../../Engine/Nodes/UI/UICollider.h"

class Dock;


class DockGridCollider : public UICollider {
public:
    static std::shared_ptr<DockGridCollider>
    create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<Dock> dock,
           int render_priority = 0);

    explicit DockGridCollider(std::shared_ptr<ContainerNode> parent, int render_priority = 0) : UICollider(parent,
                                                                                                           render_priority) {}

    static void
    setup(std::shared_ptr<DockGridCollider> node, std::shared_ptr<Dock> dock);

    void on_mouse_release(sf::Event &event, EngineContext &ctx) override;

    void on_mouse_moved(sf::Event &event, EngineContext &ctx) override;

    void on_mouse_exit(EngineContext &ctx) override;

    void on_mouse_enter(EngineContext &ctx) override;

    std::weak_ptr<Dock> dock;
};


#endif //LOGISTICHELL_DOCKGRIDCOLLIDER_H
