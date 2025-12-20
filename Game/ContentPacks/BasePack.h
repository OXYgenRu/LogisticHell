//
// Created by EgorRychkov on 14.12.2025.
//

#ifndef LOGISTICHELL_BASEPACK_H
#define LOGISTICHELL_BASEPACK_H

#include "../MainScene/ContentPack/ContentPack.h"

class BasePack : public ContentPacks::ContentPack {
public:
    unsigned int player_id;
    unsigned int input_listener_id;

    void on_world_open(Api &api) override;

    std::vector<ContentPacks::Dependence> get_dependencies() override;

    BasePack(const std::string &pack_name, unsigned int &pack_id) : ContentPack(pack_name, pack_id) {};

};


#endif //LOGISTICHELL_BASEPACK_H
