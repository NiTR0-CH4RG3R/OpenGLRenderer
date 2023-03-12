#ifndef DRAWABLE_HPP_INCLUDED
#define DRAWABLE_HPP_INCLUDED

#include <glm/glm.hpp>


class Drawable {
public:
    Drawable(
             const glm::vec3& position = glm::vec3( 0.0f, 0.0f, 0.0f ),
             const glm::vec3& rotation = glm::vec3( 0.0f, 0.0f, 0.0f ),
             const glm::vec3& scale = glm::vec3( 1.0f, 1.0f, 1.0f )
             );

    virtual ~Drawable();

    virtual void Draw( const glm::mat4& camera_transform ) = 0;

public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};


#endif // DRAWABLE_HPP_INCLUDED
