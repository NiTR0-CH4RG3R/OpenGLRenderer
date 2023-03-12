#ifndef SAMPLE_CUBE_3D_HPP_INCLUDED
#define SAMPLE_CUBE_3D_HPP_INCLUDED

#include "../third_party/glad.h"
#include "../engine/glrUtility.hpp"

#include <glm/glm.hpp>

namespace samples {
    class Cube3D {
    public:
        Cube3D();
        ~Cube3D();

        void Render( const float dt );

    public:
        GLuint VAO = 0;
        GLuint VBO = 0;
        GLuint EBO = 0;
        GLuint program = 0;
        size_t index_count = 0;

        glm::vec3 position = { 0.0f, 0.0f, 3.0f };
        glm::vec3 rotation_eular = { 0.0f, 0.0f, 0.0f };
        glm::mat4 projection_matrix { 0 };

    };
}


#endif // SAMPLE_CUBE_3D_HPP_INCLUDED
