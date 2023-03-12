#ifndef UTILITY_HPP_INCLUDED
#define UTILITY_HPP_INCLUDED

#include "../third_party/glad.h"

#include <vector>
#include <string>

namespace glr {
    namespace utility {
        GLuint CreateShaderProgram( const std::vector<std::pair<GLenum, std::string>>& shadersources );
        GLuint CreateShaderProgramFromFiles( const std::vector<std::pair<GLenum, std::string>>& shaderpaths );
        GLuint CreateShaderProgramFromName( const std::string& name );
    }
}

#endif // UTILITY_HPP_INCLUDED
