//
// Created by EgorRychkov on 03.01.2026.
//

#ifndef LOGISTICHELL_JOINTPACK_H
#define LOGISTICHELL_JOINTPACK_H


#include "../MainScene/ContentPack/ContentPack.h"

class JointPack : public ContentPacks::ContentPack {
public:
    JointPack(const std::string &pack_name, unsigned int &pack_id) : ContentPack(pack_name, pack_id) {};

    std::vector<ContentPacks::Dependence> get_dependencies() override;

    void on_world_open(Api &api) override;
};



#endif //LOGISTICHELL_JOINTPACK_H
