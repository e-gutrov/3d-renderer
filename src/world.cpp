//
// Created by egor on 07.02.2021.
//

#include "world.h"

void World::AddObject(const Triangle4D& tr) {
    objects_.push_back(tr);
}

const std::vector<Triangle4D>& World::GetObjects() const {
    return objects_;
}