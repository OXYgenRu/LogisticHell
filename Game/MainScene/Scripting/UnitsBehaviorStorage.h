//
// Created by EgorRychkov on 28.07.2025.
//

#ifndef LOGISTICHELL_UNITSBEHAVIORSTORAGE_H
#define LOGISTICHELL_UNITSBEHAVIORSTORAGE_H

#include <SFML/Window/Event.hpp>
#include "unordered_map"
#include "../../../Engine/EngineContext.h"
#include "Api/Api.h"


class UnitBehavior {
public:
    virtual void update(const unsigned int &unit_id, float last_frame_delta_time, Api &api) {}
};

class UnitsBehaviorStorage {
private:
    std::unordered_map<unsigned int, std::shared_ptr<UnitBehavior>> units;
public:
    void set_unit_behavior(const unsigned int &unit_index, const std::shared_ptr<UnitBehavior> &behavior);

    std::shared_ptr<UnitBehavior> &get_unit_behavior(const unsigned int &unit_index);
};


#endif //LOGISTICHELL_UNITSBEHAVIORSTORAGE_H
