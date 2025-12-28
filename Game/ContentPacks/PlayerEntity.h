//
// Created by EgorRychkov on 28.12.2025.
//

#ifndef LOGISTICHELL_PLAYERENTITY_H
#define LOGISTICHELL_PLAYERENTITY_H

#include "../MainScene/ContentPack/ContentPack.h"


class PlayerEntity : public ContentPacks::ContentPack {
public:
    PlayerEntity(const std::string &pack_name, unsigned int &pack_id) : ContentPack(pack_name, pack_id) {};

    std::vector <ContentPacks::Dependence> get_dependencies() override;

    void on_world_open(Api &api) override;
};


#endif //LOGISTICHELL_PLAYERENTITY_H
