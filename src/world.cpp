#include "world.h"

namespace Renderer {
void World::AddObject(const Triangle4d &tr) { objects_.push_back(tr); }

const std::vector<Triangle4d> &World::GetObjects() const { return objects_; }
}  // namespace Renderer