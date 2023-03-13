#include "MonkeyWithLight.hpp"
#include "OBJLoader.h"
#include "../engine/glrUtility.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
};

MonkeyWithLight::MonkeyWithLight()
{
    sAppName = "Monkey Face with a Point light";
}

void MonkeyWithLight::OnStart() {
    glViewport( 0, 0, (GLsizei)pWindow->GetWidth(), (GLsizei)pWindow->GetHeight() );

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace( GL_FRONT );
    glDepthFunc(GL_LESS);

    m4ProjectionMatrix = glm::perspectiveFovLH( glm::radians(90.0f), (float)(pWindow->GetWidth()), (float)(pWindow->GetHeight()), 0.01f, 100.0f );

    // Load the model using my loader
    OBJLoader loader("./assets/monkey_high.obj");

    // Store vertex information on our vertex structure array
    std::vector<Vertex> vModelVertices(loader.vertices.size());
    for (size_t i = 0; i < loader.vertices.size(); i++) {
        const auto& inVertex = loader.vertices.at(i);
        Vertex& outVertex = vModelVertices[i];

        outVertex.position = glm::vec3(inVertex.Position.x, inVertex.Position.y, inVertex.Position.z);
        outVertex.normal = glm::vec3(inVertex.Normal.x, inVertex.Normal.y, inVertex.Normal.z);
        outVertex.uv = glm::vec2(inVertex.UV.x, inVertex.UV.y);
    }

    nModelIndexCount = loader.indices.size();

    glGenVertexArrays( 1, &nModelVAO );
    glGenBuffers( 1, &nModelVBO );
    glGenBuffers( 1, &nModelEBO );

    nModelSHP = glr::utility::CreateShaderProgramFromName( "MonkeyWithLightModel" );

    glBindVertexArray( nModelVAO );

    glBindBuffer( GL_ARRAY_BUFFER, nModelVBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vModelVertices[0] ) * vModelVertices.size(), vModelVertices.data(), GL_STATIC_DRAW );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, nModelEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(loader.indices[0]) * loader.indices.size(), loader.indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vertex::position)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vertex::position) + sizeof(Vertex::normal)));
    glEnableVertexAttribArray(2);

    glBindVertexArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );


    u_m4TransformMatrix = glGetUniformLocation( nModelSHP, "u_m4TransformMatrix" );
    u_m4ViewMatrix = glGetUniformLocation( nModelSHP, "u_m4ViewMatrix" );
    u_m4NormalTransformMatrix = glGetUniformLocation( nModelSHP, "u_m4NormalTransformMatrix" );
    u_f3PLposition = glGetUniformLocation( nModelSHP, "u_f3PLposition" );
    u_f3PLcolor = glGetUniformLocation( nModelSHP, "u_f3PLcolor" );
    u_f3PLambiant = glGetUniformLocation( nModelSHP, "u_f3PLambiant" );
    u_f3PLattenuation = glGetUniformLocation( nModelSHP, "u_f3PLattenuation" );
    u_f3Mcolor = glGetUniformLocation( nModelSHP, "u_f3Mcolor" );
    u_fSpecularIntensity = glGetUniformLocation( nModelSHP, "u_fSpecularIntensity" );
    u_fSpecularPower = glGetUniformLocation( nModelSHP, "u_fSpecularPower" );

    std::vector<glm::vec3> vLightCubeVertices = {
        glm::vec3(-1.0f, -1.0f, -1.0f ) * 0.1f,
        glm::vec3(-1.0f,  1.0f, -1.0f ) * 0.1f,
        glm::vec3( 1.0f,  1.0f, -1.0f ) * 0.1f,
        glm::vec3( 1.0f, -1.0f, -1.0f ) * 0.1f,
        glm::vec3( 1.0f, -1.0f, -1.0f ) * 0.1f,
        glm::vec3( 1.0f,  1.0f, -1.0f ) * 0.1f,
        glm::vec3( 1.0f,  1.0f,  1.0f ) * 0.1f,
        glm::vec3( 1.0f, -1.0f,  1.0f ) * 0.1f,
        glm::vec3( 1.0f, -1.0f,  1.0f ) * 0.1f,
        glm::vec3( 1.0f,  1.0f,  1.0f ) * 0.1f,
        glm::vec3(-1.0f,  1.0f,  1.0f ) * 0.1f,
        glm::vec3(-1.0f, -1.0f,  1.0f ) * 0.1f,
        glm::vec3(-1.0f, -1.0f,  1.0f ) * 0.1f,
        glm::vec3(-1.0f,  1.0f,  1.0f ) * 0.1f,
        glm::vec3(-1.0f,  1.0f, -1.0f ) * 0.1f,
        glm::vec3(-1.0f, -1.0f, -1.0f ) * 0.1f,
        glm::vec3(-1.0f,  1.0f, -1.0f ) * 0.1f,
        glm::vec3(-1.0f,  1.0f,  1.0f ) * 0.1f,
        glm::vec3( 1.0f,  1.0f,  1.0f ) * 0.1f,
        glm::vec3( 1.0f,  1.0f, -1.0f ) * 0.1f,
        glm::vec3(-1.0f, -1.0f,  1.0f ) * 0.1f,
        glm::vec3(-1.0f, -1.0f, -1.0f ) * 0.1f,
        glm::vec3( 1.0f, -1.0f, -1.0f ) * 0.1f,
        glm::vec3( 1.0f, -1.0f,  1.0f ) * 0.1f,
    };

    std::vector<unsigned int> vLightCubeIndices = {
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

    nPointLightIndexCount = vLightCubeIndices.size();

    glGenVertexArrays( 1, &nPointLightVAO );
    glGenBuffers( 1, &nPointLightVBO );
    glGenBuffers( 1, &nPointLightEBO );

    nPointLightSHP = glr::utility::CreateShaderProgramFromName( "MonkeyWithLightLight" );

    glBindVertexArray( nPointLightVAO );

    glBindBuffer( GL_ARRAY_BUFFER, nPointLightVBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vLightCubeVertices[0] ) * vLightCubeVertices.size(), vLightCubeVertices.data(), GL_STATIC_DRAW );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, nPointLightEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vLightCubeIndices[0]) * vLightCubeIndices.size(), vLightCubeIndices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

}

void MonkeyWithLight::OnUpdate( const float dt ) {


    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glm::mat4 camera_rotation_matrix = glm::rotate( glm::mat4(1.0f), v3CameraRotation.y, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    camera_rotation_matrix = glm::rotate( camera_rotation_matrix, v3CameraRotation.x, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    camera_rotation_matrix = glm::rotate( camera_rotation_matrix, v3CameraRotation.z, glm::vec3( 0.0f, 0.0f, 1.0f ) );

    if ( pWindow->GetKey( glr::Keys::W ) ) { v3CameraPosition += glm::vec3( camera_rotation_matrix * glm::vec4( 0.0f, 0.0f, 1.0f, 1.0f ) * fCameraMoveSpeed * dt ); }
    if ( pWindow->GetKey( glr::Keys::S ) ) { v3CameraPosition -= glm::vec3( camera_rotation_matrix * glm::vec4( 0.0f, 0.0f, 1.0f, 1.0f ) * fCameraMoveSpeed * dt ); }
    if ( pWindow->GetKey( glr::Keys::D ) ) { v3CameraPosition += glm::vec3( camera_rotation_matrix * glm::vec4( 1.0f, 0.0f, 0.0f, 1.0f ) * fCameraMoveSpeed * dt ); }
    if ( pWindow->GetKey( glr::Keys::A ) ) { v3CameraPosition -= glm::vec3( camera_rotation_matrix * glm::vec4( 1.0f, 0.0f, 0.0f, 1.0f ) * fCameraMoveSpeed * dt ); }
    if ( pWindow->GetKey( glr::Keys::Q ) ) { v3CameraPosition += glm::vec3( camera_rotation_matrix * glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f ) * fCameraMoveSpeed * dt ); }
    if ( pWindow->GetKey( glr::Keys::E ) ) { v3CameraPosition -= glm::vec3( camera_rotation_matrix * glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f ) * fCameraMoveSpeed * dt ); }


    if ( pWindow->GetKey( glr::Keys::I ) ) { v3CameraRotation.x -= fCameraRotateSpeed * dt; v3CameraRotation.x = v3CameraRotation.x <= 0.0f ? ( 2.0f * glm::pi<float>() ) : v3CameraRotation.x; }
    if ( pWindow->GetKey( glr::Keys::K ) ) { v3CameraRotation.x += fCameraRotateSpeed * dt; v3CameraRotation.x = v3CameraRotation.x >= ( 2.0f * glm::pi<float>() ) ? 0.0f : v3CameraRotation.x; }
    if ( pWindow->GetKey( glr::Keys::J ) ) { v3CameraRotation.y -= fCameraRotateSpeed * dt; v3CameraRotation.y = v3CameraRotation.y <= 0.0f ? ( 2.0f * glm::pi<float>() ) : v3CameraRotation.y; }
    if ( pWindow->GetKey( glr::Keys::L ) ) { v3CameraRotation.y += fCameraRotateSpeed * dt; v3CameraRotation.y = v3CameraRotation.y >= ( 2.0f * glm::pi<float>() ) ? 0.0f : v3CameraRotation.y; }
    if ( pWindow->GetKey( glr::Keys::U ) ) { v3CameraRotation.z -= fCameraRotateSpeed * dt; v3CameraRotation.z = v3CameraRotation.z <= 0.0f ? ( 2.0f * glm::pi<float>() ) : v3CameraRotation.z; }
    if ( pWindow->GetKey( glr::Keys::O ) ) { v3CameraRotation.z += fCameraRotateSpeed * dt; v3CameraRotation.z = v3CameraRotation.z >= ( 2.0f * glm::pi<float>() ) ? 0.0f : v3CameraRotation.z; }

    if ( pWindow->GetKey( glr::Keys::KP_8 ) ) { v3PointLightPosition += glm::vec3( camera_rotation_matrix * glm::vec4( 0.0f, 0.0f, 1.0f, 1.0f ) * fCameraMoveSpeed * dt ); }
    if ( pWindow->GetKey( glr::Keys::KP_2 ) ) { v3PointLightPosition -= glm::vec3( camera_rotation_matrix * glm::vec4( 0.0f, 0.0f, 1.0f, 1.0f ) * fCameraMoveSpeed * dt ); }
    if ( pWindow->GetKey( glr::Keys::KP_6 ) ) { v3PointLightPosition += glm::vec3( camera_rotation_matrix * glm::vec4( 1.0f, 0.0f, 0.0f, 1.0f ) * fCameraMoveSpeed * dt ); }
    if ( pWindow->GetKey( glr::Keys::KP_4 ) ) { v3PointLightPosition -= glm::vec3( camera_rotation_matrix * glm::vec4( 1.0f, 0.0f, 0.0f, 1.0f ) * fCameraMoveSpeed * dt ); }
    if ( pWindow->GetKey( glr::Keys::KP_7 ) ) { v3PointLightPosition += glm::vec3( camera_rotation_matrix * glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f ) * fCameraMoveSpeed * dt ); }
    if ( pWindow->GetKey( glr::Keys::KP_9 ) ) { v3PointLightPosition -= glm::vec3( camera_rotation_matrix * glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f ) * fCameraMoveSpeed * dt ); }

    if ( pWindow->GetKey( glr::Keys::M ) ) { fSpecularIntensity =  std::max( 0.0f, fSpecularIntensity + 1.0f * dt ); }
    if ( pWindow->GetKey( glr::Keys::N ) ) { fSpecularIntensity =  std::max( 0.0f, fSpecularIntensity - 1.0f * dt ); }
    if ( pWindow->GetKey( glr::Keys::B ) ) { fSpecularPower =  std::max( 0.0f, fSpecularPower + 10.0f * dt ); }
    if ( pWindow->GetKey( glr::Keys::V ) ) { fSpecularPower =  std::max( 0.0f, fSpecularPower - 10.0f * dt ); }


    if ( bModelShouldRotate ) {
            v3ModelRotation.y = v3ModelRotation.y + fModelRotateSpeed * dt ;
            v3ModelRotation.y = v3ModelRotation.y >= ( 2.0f * glm::pi<float>() ) ? 0.0f : v3ModelRotation.y;
    }



    {
        ImGui::Begin("Propoerties");
        ImGui::Text("frametime : %.3f ms\nframerate : %.1f FPS\n", 1000.0f / pIO->Framerate, pIO->Framerate);

        ImGui::Text( "Light Propoerties" );
        ImGui::DragFloat3( "Light Position", (float*)&v3PointLightPosition, 0.1f, -100.0f, 100.0f, NULL, 0 );
        ImGui::ColorEdit3("Light Color", (float*)&v3PointLightColor );
        ImGui::ColorEdit3("Light Ambiant", (float*)&v3PointLightAmbiant );
        ImGui::SliderFloat3( "Light Attenuation", (float*)&v3PointLightAttenuation, 0.0f, 1.0f, NULL, 0 );
        ImGui::DragFloat( "Light Specular Intesity", &fSpecularIntensity, 0.01f, 0.0f, 100.0f, NULL, 0 );
        ImGui::DragFloat( "Light Specular Power", &fSpecularPower, 0.1f, 0.0f, 500.0f, NULL, 0 );

        ImGui::Text( "Model Propoerties" );
        ImGui::DragFloat3( "Model Position", (float*)&v3ModelPosition, 0.1f, -100.0f, 100.0f, NULL, 0 );
        ImGui::DragFloat3( "Model Rotation", (float*)&v3ModelRotation, 0.1f, -100.0f, 100.0f, NULL, 0 );
        ImGui::DragFloat3( "Model Scale", (float*)&v3ModelScale, 0.1f, 0.0f, 100.0f, NULL, 0 );
        ImGui::ColorEdit3("Model Color", (float*)&v3ModelColor );
        ImGui::Checkbox( "Model Should Rotate", &bModelShouldRotate );

        ImGui::Text( "Camera Propoerties" );
        ImGui::DragFloat3( "Camera Position", (float*)&v3CameraPosition, 0.1f, -100.0f, 100.0f, NULL, 0 );
        ImGui::DragFloat3( "Camera Rotation", (float*)&v3CameraRotation, 0.1f, -100.0f, 100.0f, NULL, 0 );
        ImGui::DragFloat( "Camera Move Speed", &fCameraMoveSpeed, 0.1f, -100.0f, 100.0f, NULL, 0 );
        ImGui::DragFloat( "Camera Rotate Speed", &fCameraRotateSpeed, 0.1f, -100.0f, 100.0f, NULL, 0 );


        ImGui::End();
    }


    glUseProgram(nModelSHP);

    glm::mat4 transform_matrix = glm::rotate( m4ProjectionMatrix, -v3CameraRotation.z, glm::vec3( 0.0f, 0.0f, 1.0f ) );
    transform_matrix = glm::rotate( transform_matrix, -v3CameraRotation.x, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    transform_matrix = glm::rotate( transform_matrix, -v3CameraRotation.y, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    transform_matrix = glm::translate( transform_matrix, -v3CameraPosition );
    transform_matrix = glm::translate( transform_matrix, v3ModelPosition );
    transform_matrix = glm::rotate( transform_matrix, v3ModelRotation.y, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    transform_matrix = glm::rotate( transform_matrix, v3ModelRotation.x, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    transform_matrix = glm::rotate( transform_matrix, v3ModelRotation.z, glm::vec3( 0.0f, 0.0f, 1.0f ) );
    transform_matrix = glm::scale( transform_matrix, v3ModelScale );
    glUniformMatrix4fv( u_m4TransformMatrix, 1, GL_FALSE, glm::value_ptr(transform_matrix) );


    transform_matrix = glm::rotate( glm::mat4(1.0f), -v3CameraRotation.z, glm::vec3( 0.0f, 0.0f, 1.0f ) );
    transform_matrix = glm::rotate( transform_matrix, -v3CameraRotation.x, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    transform_matrix = glm::rotate( transform_matrix, -v3CameraRotation.y, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    transform_matrix = glm::translate( transform_matrix, -v3CameraPosition );

    glm::vec4 v4PointLightViewPosition =  transform_matrix * glm::vec4( v3PointLightPosition.x, v3PointLightPosition.y, v3PointLightPosition.z, 1.0f );
    glm::vec3 v3PointLightViewPosition = glm::vec3( v4PointLightViewPosition.x, v4PointLightViewPosition.y, v4PointLightViewPosition.z );

    transform_matrix = glm::translate( transform_matrix, v3ModelPosition );
    transform_matrix = glm::rotate( transform_matrix, v3ModelRotation.y, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    transform_matrix = glm::rotate( transform_matrix, v3ModelRotation.x, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    transform_matrix = glm::rotate( transform_matrix, v3ModelRotation.z, glm::vec3( 0.0f, 0.0f, 1.0f ) );
    transform_matrix = glm::scale( transform_matrix, v3ModelScale );
    glUniformMatrix4fv( u_m4ViewMatrix, 1, GL_FALSE, glm::value_ptr(transform_matrix) );


    transform_matrix = glm::rotate( glm::mat4(1.0f), -v3CameraRotation.z, glm::vec3( 0.0f, 0.0f, 1.0f ) );
    transform_matrix = glm::rotate( transform_matrix, -v3CameraRotation.x, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    transform_matrix = glm::rotate( transform_matrix, -v3CameraRotation.y, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    transform_matrix = glm::rotate( transform_matrix, v3ModelRotation.y, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    transform_matrix = glm::rotate( transform_matrix, v3ModelRotation.x, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    transform_matrix = glm::rotate( transform_matrix, v3ModelRotation.z, glm::vec3( 0.0f, 0.0f, 1.0f ) );
    glUniformMatrix4fv( u_m4NormalTransformMatrix, 1, GL_FALSE, glm::value_ptr(transform_matrix) );

    glUniform3fv( u_f3PLposition, 1, glm::value_ptr(v3PointLightViewPosition) );
    glUniform3fv( u_f3PLcolor, 1, glm::value_ptr(v3PointLightColor) );
    glUniform3fv( u_f3PLambiant, 1, glm::value_ptr(v3PointLightAmbiant) );
    glUniform3fv( u_f3PLattenuation, 1, glm::value_ptr(v3PointLightAttenuation) );
    glUniform3fv( u_f3Mcolor, 1, glm::value_ptr(v3ModelColor) );

    glUniform1f( u_fSpecularIntensity, fSpecularIntensity );
    glUniform1f( u_fSpecularPower, fSpecularPower );

    glBindVertexArray(nModelVAO);
    glDrawElements(GL_TRIANGLES, nModelIndexCount, GL_UNSIGNED_INT, 0);

    glUseProgram(nPointLightSHP);

    transform_matrix = glm::rotate( m4ProjectionMatrix, -v3CameraRotation.z, glm::vec3( 0.0f, 0.0f, 1.0f ) );
    transform_matrix = glm::rotate( transform_matrix, -v3CameraRotation.x, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    transform_matrix = glm::rotate( transform_matrix, -v3CameraRotation.y, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    transform_matrix = glm::translate( transform_matrix, -v3CameraPosition );
    transform_matrix = glm::translate( transform_matrix, v3PointLightPosition );
    glUniformMatrix4fv( 0, 1, GL_FALSE, glm::value_ptr(transform_matrix) );
    glUniform3fv( 1, 1, glm::value_ptr( v3PointLightColor ) );

    glBindVertexArray(nPointLightVAO);
    glDrawElements(GL_TRIANGLES, nPointLightIndexCount, GL_UNSIGNED_INT, 0);
}

void MonkeyWithLight::OnStop() {

}
