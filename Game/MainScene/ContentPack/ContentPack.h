//
// Created by EgorRychkov on 14.12.2025.
//

#ifndef LOGISTICHELL_CONTENTPACK_H
#define LOGISTICHELL_CONTENTPACK_H

#include <memory>
#include <utility>
#include <variant>
#include "SFML/Graphics.hpp"


class Api;

namespace ContentPacks {
    enum class DependenceType {
        Hard,
        Presence,
        Optional
    };

    class Dependence {
    private:
        std::string pack_name;
        DependenceType type;
    public:
        explicit Dependence(std::string pack_name, const DependenceType &type) : pack_name(std::move(pack_name)),
                                                                                 type(type) {}

        [[nodiscard]] const std::string &get_pack() const { return pack_name; }

        [[nodiscard]] const DependenceType &get_type() const { return type; }
    };

    class ContentPack {
    private:
        unsigned int pack_id;
        std::string pack_name;
    public:
        ContentPack(const std::string &pack_name, unsigned int &pack_id);

        virtual std::vector<Dependence> get_dependencies() = 0;

        virtual void on_world_open(Api &api) {}

        [[nodiscard]] const std::string &get_pack_name() const;
    };
}


#endif //LOGISTICHELL_CONTENTPACK_H
