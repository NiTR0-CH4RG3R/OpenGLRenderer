#include "glrUtility.hpp"

#include "glrAssert.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

bool __ReadFileToString( const std::string& filepath, std::string& str ) {
    std::ifstream t(filepath);

    ASSERT_IF_DEBUG( t.is_open() );

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)),
                std::istreambuf_iterator<char>());

    return true;
}

GLuint __CreateShader( const GLenum type, const std::string& source ) {
    GLuint shader = glCreateShader( type );
    const char* pShaderSource = source.c_str();
    glShaderSource( shader, 1, &pShaderSource, NULL );
    glCompileShader( shader );

    int  success = 0;
    char infoLog[512] { 0 };
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        assert( success );
    }

    return shader;
}

GLuint glr::utility::CreateShaderProgram( const std::vector<std::pair<GLenum, std::string>>& shadersources ) {
    GLuint program = 0;

    std::vector<GLuint> shaders = {};
    for ( const auto& shadersource : shadersources ) {
        shaders.push_back( __CreateShader( shadersource.first, shadersource.second ) );
    }

    program = glCreateProgram();

    for ( const auto& shader : shaders ) {
        glAttachShader( program, shader );
    }

    glLinkProgram( program );

    for ( const auto& shader : shaders ) {
        glDeleteShader( shader );
    }

    int  success = 0;
    char infoLog[512] { 0 };

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
        assert( success );
    }

    return program;
}


GLuint glr::utility::CreateShaderProgramFromFiles( const std::vector<std::pair<GLenum, std::string>>& shaderpaths ) {
    std::vector<std::pair<GLenum, std::string>> shadersources( shaderpaths.size() );
    for ( size_t i = 0; i < shadersources.size(); i++ ) {
        shadersources[i].first = shaderpaths[i].first;
        ASSERT_IF_DEBUG( __ReadFileToString( shaderpaths[i].second, shadersources[i].second ) );
        std::cout << shadersources[i].second << std::endl;
    }

    return CreateShaderProgram( shadersources );
}

GLuint glr::utility::CreateShaderProgramFromName( const std::string& name ) {
    std::string VertexShaderPath = "./shaders/" + name + ".vert";
    std::string FragmentShaderPath = "./shaders/" + name + ".frag";

    return CreateShaderProgramFromFiles( {
                                        std::pair<GLenum, std::string>( GL_VERTEX_SHADER, VertexShaderPath ),
                                        std::pair<GLenum, std::string>( GL_FRAGMENT_SHADER, FragmentShaderPath ),
                                        } );
}
