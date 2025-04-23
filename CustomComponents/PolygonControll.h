//
// Created by EgorRychkov on 17.04.2025.
//

#ifndef LOGISTICHELL_POLYGONCONTROLL_H
#define LOGISTICHELL_POLYGONCONTROLL_H


#include "../Engine/Nodes/Base/ContainerNode.h"
#include "../Engine/Nodes/Control/Controller.h"

class PolygonControll : public Controller {
public:
    explicit PolygonControll(std::shared_ptr<ContainerNode> parent, int render_priority = 0) : Controller(parent,
                                                                                                          render_priority) {}

    static std::shared_ptr<PolygonControll> create(std::shared_ptr<ContainerNode> parent, int render_priority = 0);


    void update(EngineContext &ctx);

    void on_mouse_press(sf::Event &event, EngineContext &ctx);
};


#endif //LOGISTICHELL_POLYGONCONTROLL_H
