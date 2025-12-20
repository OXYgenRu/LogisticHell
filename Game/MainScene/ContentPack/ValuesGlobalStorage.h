//
// Created by EgorRychkov on 14.12.2025.
//

#ifndef LOGISTICHELL_VALUESGLOBALSTORAGE_H
#define LOGISTICHELL_VALUESGLOBALSTORAGE_H


#include <variant>
#include <unordered_map>
#include <string>
#include <optional>
#include <iostream>

namespace Scripting {
    struct Value {
    public:
        using Variant = std::variant<std::monostate, unsigned int>;

        Value() = default;

        template<typename T>
        Value(T v) : data(std::move(v)) {}

        bool is_null() const { return std::holds_alternative<std::monostate>(data); }

        template<typename T>
        bool is() const { return std::holds_alternative<T>(data); }

        template<typename T>
        T &as() { return std::get<T>(data); }

        template<typename T>
        const T &as() const {
            return std::get<T>(data);
        }

        size_t get_index() {
            return data.index();
        }

    private:
        Variant data;
    };
}


class ValuesGlobalStorage {
private:
    std::unordered_map<std::string, std::unordered_map<std::string, Scripting::Value>> values;
public:
    ValuesGlobalStorage() = default;

    bool set(const std::string &namespace_, const std::string &name, Scripting::Value value);


    std::optional<Scripting::Value> get(const std::string &namespace_, const std::string &name) const {
        auto it_1 = values.find(namespace_);
        if (it_1 == values.end()) {
            std::cout << "ValuesGlobalStorage: namespace not found" << '\n';
            return std::nullopt;
        }
        auto it_2 = it_1->second.find(name);
        if (it_2 == it_1->second.end()) {
            return std::nullopt;
        }
        return it_2->second;
    }

    void create_namespace(const std::string &namespace_);
};


#endif //LOGISTICHELL_VALUESGLOBALSTORAGE_H
