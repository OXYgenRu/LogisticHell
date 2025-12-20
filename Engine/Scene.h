//
// Created by EgorRychkov on 13.04.2025.
//

#include "Nodes/Base/Node.h"

#ifndef LOGISTICHELL_SCENE_H
#define LOGISTICHELL_SCENE_H

#include "EngineContext.h"

class Scene : public Node {
public:
    Scene(const std::string &node_id) : Node(nullptr, node_id) {}

    static std::shared_ptr<Scene> create(const std::string &node_id); // TODO override

    int get_node_type() const override;

    virtual void init_tree(EngineContext &ctx);
};


#endif //LOGISTICHELL_SCENE_H
