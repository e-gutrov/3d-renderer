#include "world.h"

void World::AddObject(const Triangle4d& tr) {
    Objects_.push_back(tr);
}

const std::vector<Triangle4d>& World::GetObjects() const {
    return Objects_;
}