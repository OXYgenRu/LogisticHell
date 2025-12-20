//
// Created by EgorRychkov on 14.12.2025.
//

#include "ContentPack.h"

ContentPacks::ContentPack::ContentPack(const std::string &pack_name, unsigned int &pack_id) {
    this->pack_name = pack_name;
    this->pack_id = pack_id;
}

const std::string &ContentPacks::ContentPack::get_pack_name() const {
    return pack_name;
}