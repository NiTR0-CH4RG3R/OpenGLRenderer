#include "ecsBuiltinRootTransform.hpp"

ecs::builtin_comps::RootTransform::RootTransform( Entity* pParent ) : Transform( pParent, glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ) ) {
}
