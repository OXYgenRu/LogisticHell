//
// Created by EgorRychkov on 02.05.2025.
//

#ifndef LOGISTICHELL_DOCKCONTROLLER_H
#define LOGISTICHELL_DOCKCONTROLLER_H

#include "../../../../Engine/Nodes/Control/Controller.h"

class Dock;

class DockController : public Controller {
public:
    static std::shared_ptr<DockController>
    create(std::shared_ptr<ContainerNode> parent, std::shared_ptr<Dock> dock, int render_priority = 0);

    explicit DockController(std::shared_ptr<ContainerNode> parent, int render_priority = 0) : Controller(parent,
                                                                                                         render_priority) {}

    virtual void on_key_release(sf::Event &event, EngineContext &ctx);

    std::weak_ptr<Dock> dock;
};


#endif //LOGISTICHELL_DOCKCONTROLLER_H
