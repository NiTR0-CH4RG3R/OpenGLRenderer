#ifndef SAMPLE_QUAD_HPP_INCLUDED
#define SAMPLE_QUAD_HPP_INCLUDED

#include "../third_party/glad.h"
#include "../engine/glrUtility.hpp"

namespace samples {
    class Quad {
    public:
        Quad();
        ~Quad();

        void Render();

    private:
        GLuint VAO = 0;
        GLuint VBO = 0;
        GLuint EBO = 0;
        GLuint program = 0;
        size_t index_count = 0;
    };
}

#endif // SAMPLE_QUAD_HPP_INCLUDED
