#ifndef MONKEYWITHLIGHT_H
#define MONKEYWITHLIGHT_H

#include "../engine/glrEngine.hpp"

#include "../third_party/glad.h"
#include <glm/glm.hpp>

class MonkeyWithLight : public glr::Engine
{
public:
    MonkeyWithLight();

private:
    void OnStart() override;
    void OnUpdate( const float dt ) override;
    void OnStop() override;

private:
    GLuint nModelVBO = 0;
    GLuint nModelEBO = 0;
    GLuint nModelVAO = 0;
    GLuint nModelSHP = 0;

    size_t nModelIndexCount = 0;

    glm::vec3 v3ModelPosition = glm::vec3( 0.0f, 0.0f, 5.0f );
    glm::vec3 v3ModelRotation = glm::vec3( 0.0f, 0.0f, 0.0f );
    glm::vec3 v3ModelScale = glm::vec3( 1.0f, 1.0f, 1.0f );
    float fModelMoveSpeed = 5.0f;
    float fModelRotateSpeed = 1.0f;
    bool bModelShouldRotate = false;

    glm::vec3 v3ModelColor = glm::vec3( 0.8f, 0.8f, 1.0f );

    glm::vec3 v3CameraPosition = glm::vec3( 0.0f, 0.0f, 0.0f );
    glm::vec3 v3CameraRotation = glm::vec3( 0.0f, 0.0f, 0.0f );
    float fCameraMoveSpeed = 5.0f;
    float fCameraRotateSpeed = 3.0f;

    glm::vec3 v3PointLightPosition =    glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 v3PointLightColor =       glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 v3PointLightAmbiant =     glm::vec3(0.1f, 0.1f, 0.1f);
    glm::vec3 v3PointLightAttenuation = glm::vec3(0.0028f, 0.027f, 1.0f);

    GLuint nPointLightVBO = 0;
    GLuint nPointLightEBO = 0;
    GLuint nPointLightVAO = 0;
    GLuint nPointLightSHP = 0;

    size_t nPointLightIndexCount = 0;

    // Specluar properties
    float fSpecularIntensity = 0.6f;
    float fSpecularPower = 30.0f;

    glm::mat4 m4ProjectionMatrix = glm::mat4( 1.0f );


    // Uniforms
    GLint u_m4TransformMatrix;
    GLint u_m4ViewMatrix;
    GLint u_m4NormalTransformMatrix;
    GLint u_f3PLposition;
    GLint u_f3PLcolor;
    GLint u_f3PLambiant;
    GLint u_f3PLattenuation;
    GLint u_f3Mcolor;
    GLint u_fSpecularIntensity;
    GLint u_fSpecularPower;


    bool show_demo_window = true;
};

#endif // MONKEYWITHLIGHT_H
