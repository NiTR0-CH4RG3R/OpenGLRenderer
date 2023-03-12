#include "sample_cube_3d.hpp"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace samples {

    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };

    Cube3D::Cube3D() {
        std::vector<Vertex> vertices = {
            { glm::vec3(-1.0f, -1.0f, -1.0f ), glm::vec3( 1.0f, 0.0f, 0.0f ), glm::vec2( 0.0f, 0.0f ) },
            { glm::vec3(-1.0f,  1.0f, -1.0f ), glm::vec3( 1.0f, 0.0f, 0.0f ), glm::vec2( 0.0f, 0.0f ) },
            { glm::vec3( 1.0f,  1.0f, -1.0f ), glm::vec3( 1.0f, 0.0f, 0.0f ), glm::vec2( 0.0f, 0.0f ) },
            { glm::vec3( 1.0f, -1.0f, -1.0f ), glm::vec3( 1.0f, 0.0f, 0.0f ), glm::vec2( 0.0f, 0.0f ) },

            { glm::vec3( 1.0f, -1.0f, -1.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ), glm::vec2( 0.0f, 0.0f ) },
            { glm::vec3( 1.0f,  1.0f, -1.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ), glm::vec2( 0.0f, 0.0f ) },
            { glm::vec3( 1.0f,  1.0f,  1.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ), glm::vec2( 0.0f, 0.0f ) },
            { glm::vec3( 1.0f, -1.0f,  1.0f ), glm::vec3( 0.0f, 1.0f, 0.0f ), glm::vec2( 0.0f, 0.0f ) },

            { glm::vec3( 1.0f, -1.0f,  1.0f ), glm::vec3( 0.0f, 0.0f, 1.0f ), glm::vec2( 0.0f, 0.0f ) },
            { glm::vec3( 1.0f,  1.0f,  1.0f ), glm::vec3( 0.0f, 0.0f, 1.0f ), glm::vec2( 0.0f, 0.0f ) },
            { glm::vec3(-1.0f,  1.0f,  1.0f ), glm::vec3( 0.0f, 0.0f, 1.0f ), glm::vec2( 0.0f, 0.0f ) },
            { glm::vec3(-1.0f, -1.0f,  1.0f ), glm::vec3( 0.0f, 0.0f, 1.0f ), glm::vec2( 0.0f, 0.0f ) },

            { glm::vec3(-1.0f, -1.0f,  1.0f ), glm::vec3( 1.0f, 1.0f, 0.0f ), glm::vec2( 0.0f, 0.0f ) },
            { glm::vec3(-1.0f,  1.0f,  1.0f ), glm::vec3( 1.0f, 1.0f, 0.0f ), glm::vec2( 0.0f, 0.0f ) },
            { glm::vec3(-1.0f,  1.0f, -1.0f ), glm::vec3( 1.0f, 1.0f, 0.0f ), glm::vec2( 0.0f, 0.0f ) },
            { glm::vec3(-1.0f, -1.0f, -1.0f ), glm::vec3( 1.0f, 1.0f, 0.0f ), glm::vec2( 0.0f, 0.0f ) },

            { glm::vec3(-1.0f,  1.0f, -1.0f ), glm::vec3( 0.0f, 1.0f, 1.0f ), glm::vec2( 0.0f, 0.0f ) },
            { glm::vec3(-1.0f,  1.0f,  1.0f ), glm::vec3( 0.0f, 1.0f, 1.0f ), glm::vec2( 0.0f, 0.0f ) },
            { glm::vec3( 1.0f,  1.0f,  1.0f ), glm::vec3( 0.0f, 1.0f, 1.0f ), glm::vec2( 0.0f, 0.0f ) },
            { glm::vec3( 1.0f,  1.0f, -1.0f ), glm::vec3( 0.0f, 1.0f, 1.0f ), glm::vec2( 0.0f, 0.0f ) },

            { glm::vec3(-1.0f, -1.0f,  1.0f ), glm::vec3( 1.0f, 0.0f, 1.0f ), glm::vec2( 0.0f, 0.0f ) },
            { glm::vec3(-1.0f, -1.0f, -1.0f ), glm::vec3( 1.0f, 0.0f, 1.0f ), glm::vec2( 0.0f, 0.0f ) },
            { glm::vec3( 1.0f, -1.0f, -1.0f ), glm::vec3( 1.0f, 0.0f, 1.0f ), glm::vec2( 0.0f, 0.0f ) },
            { glm::vec3( 1.0f, -1.0f,  1.0f ), glm::vec3( 1.0f, 0.0f, 1.0f ), glm::vec2( 0.0f, 0.0f ) },
        };

        std::vector<unsigned int> indices = {
            0, 1, 2,
            0, 2, 3,

            4, 5, 6,
            4, 6, 7,

            8, 9, 10,
            8, 10, 11,

            12, 13, 14,
            12, 14, 15,

            16, 17, 18,
            16, 18, 19,

            20, 21, 22,
            20, 22, 23,
        };

        index_count = indices.size();

        glGenVertexArrays( 1, &VAO );
        glGenBuffers( 1, &VBO );
        glGenBuffers( 1, &EBO );

        program = glr::utility::CreateShaderProgramFromName( "Shader3D" );

        glBindVertexArray( VAO );

        glBindBuffer( GL_ARRAY_BUFFER, VBO );
        glBufferData( GL_ARRAY_BUFFER, sizeof( vertices[0] ) * vertices.size(), vertices.data(), GL_STATIC_DRAW );

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vertex::position)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vertex::position) + sizeof(Vertex::normal)));
        glEnableVertexAttribArray(2);

        glBindVertexArray( 0 );
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

        projection_matrix  = glm::perspectiveFovLH( 90.0f, 800.0f, 600.0f, 0.01f, 100.0f );

    }

    Cube3D::~Cube3D() {
        glBindVertexArray( 0 );
        glDeleteVertexArrays( 1, &VAO );
        glDeleteBuffers( 1, &VBO );
        glDeleteProgram( program );
    }

    void Cube3D::Render( const float dt ) {
        glUseProgram(program);

        rotation_eular.x += 1 * dt;
        rotation_eular.y += 1 * dt;

//        glm::mat4 transform_matrix = glm::translate( glm::mat4(1.0f), position );
//        transform_matrix = glm::rotate( transform_matrix, rotation_eular.y, glm::vec3( 0.0f, 1.0f, 0.0f ) );
//        transform_matrix = glm::rotate( transform_matrix, rotation_eular.x, glm::vec3( 1.0f, 0.0f, 0.0f ) );
//        transform_matrix = glm::rotate( transform_matrix, rotation_eular.z, glm::vec3( 0.0f, 0.0f, 1.0f ) );
//        glUniformMatrix4fv( 0, 1, GL_FALSE, glm::value_ptr(projection_matrix) );
//        glUniformMatrix4fv( 1, 1, GL_FALSE, glm::value_ptr(transform_matrix) );

        glm::mat4 transform_matrix = glm::translate( projection_matrix, position );
        transform_matrix = glm::rotate( transform_matrix, rotation_eular.y, glm::vec3( 0.0f, 1.0f, 0.0f ) );
        transform_matrix = glm::rotate( transform_matrix, rotation_eular.x, glm::vec3( 1.0f, 0.0f, 0.0f ) );
        transform_matrix = glm::rotate( transform_matrix, rotation_eular.z, glm::vec3( 0.0f, 0.0f, 1.0f ) );
        glUniformMatrix4fv( 0, 1, GL_FALSE, glm::value_ptr(transform_matrix) );

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
    }
}
