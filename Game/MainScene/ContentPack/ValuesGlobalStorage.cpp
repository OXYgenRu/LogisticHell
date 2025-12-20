//
// Created by EgorRychkov on 14.12.2025.
//

#include <mmcobj.h>
#include "ValuesGlobalStorage.h"

bool ValuesGlobalStorage::set(const std::string &namespace_, const std::string &name, Scripting::Value value) {
    auto it_1 = values.find(namespace_);

    if (it_1 == values.end()) {
        return false;
    }
    auto it_2 = it_1->second.find(name);
    if (it_2 == it_1->second.end()) {
        values[namespace_].emplace(name, std::move(value));
        return true;
    }

    if (it_2->second.get_index() != value.get_index()) {
        return false;
    }
    it_2->second = std::move(value);
    return true;
}

void ValuesGlobalStorage::create_namespace(const std::string &namespace_) {
    values[namespace_];
}