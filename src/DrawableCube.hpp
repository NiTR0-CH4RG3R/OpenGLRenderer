#ifndef DRAWABLECUBE_HPP_INCLUDED
#define DRAWABLECUBE_HPP_INCLUDED

#include "Drawable.hpp"
#include "third_party/glad.h"


class DrawableCube : public Drawable {
private:
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };

public:
    DrawableCube();
    ~DrawableCube();

    void Draw( const glm::mat4& camera_transform ) override;

private:
    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint EBO = 0;
    GLuint program = 0;
    size_t index_count = 0;

};


#endif // DRAWABLECUBE_HPP_INCLUDED
