//
// Created by EgorRychkov on 15.12.2025.
//

#ifndef LOGISTICHELL_VALUESSTORAGEAPI_H
#define LOGISTICHELL_VALUESSTORAGEAPI_H

#include <memory>
#include "../../ContentPack/ValuesGlobalStorage.h"


class GameWorld;


class ValuesStorageApi {
private:
    std::weak_ptr<GameWorld> world;
public:
    explicit ValuesStorageApi(const std::shared_ptr<GameWorld> &world);

    bool set(const std::string &namespace_, const std::string &name, Scripting::Value value);

    std::optional<Scripting::Value> get(const std::string &namespace_, const std::string &name) const;
};


#endif //LOGISTICHELL_VALUESSTORAGEAPI_H
