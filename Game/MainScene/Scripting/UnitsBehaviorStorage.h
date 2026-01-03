//
// Created by EgorRychkov on 28.07.2025.
//

#ifndef LOGISTICHELL_UNITSBEHAVIORSTORAGE_H
#define LOGISTICHELL_UNITSBEHAVIORSTORAGE_H

#include <SFML/Window/Event.hpp>
#include "unordered_map"
#include "../../../Engine/EngineContext.h"
#include "Api/Api.h"

namespace SystemsExceptions {
    class UnitBehaviorIsNull : public std::runtime_error {
    public:
        UnitBehaviorIsNull(unsigned int unit_index, const std::string &msg)
                : std::runtime_error(msg), unit_index_(unit_index) {}

        [[nodiscard]] unsigned int unit_index() const noexcept {
            return unit_index_;
        }

    private:
        unsigned int unit_index_;
    };
}


class UnitBehavior {
public:
    virtual void on_spawn(const unsigned int &unit_id, Api &api) {}

    virtual void update(const unsigned int &unit_id, float last_frame_delta_time, Api &api) {}

    virtual void on_destroy(const unsigned int &unit_id, Api &api) {}
};

class UnitsBehaviorStorage {
private:
    std::unordered_map<unsigned int, std::shared_ptr<UnitBehavior>> units;
public:
    void set_unit_behavior(const unsigned int &unit_index, const std::shared_ptr<UnitBehavior> &behavior);

    std::shared_ptr<UnitBehavior> &get_unit_behavior(const unsigned int &unit_index);

    void on_world_open();
};


#endif //LOGISTICHELL_UNITSBEHAVIORSTORAGE_H
