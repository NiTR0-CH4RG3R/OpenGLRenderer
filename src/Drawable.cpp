#include "Drawable.hpp"

Drawable::Drawable(
                 const glm::vec3& position,
                 const glm::vec3& rotation,
                 const glm::vec3& scale
                 ) :
                     position( position ),
                     rotation( rotation ),
                     scale( scale )
                     { }

Drawable::~Drawable() {}
