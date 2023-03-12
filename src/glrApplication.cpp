#include "glrApplication.hpp"
#include "glrDrawableCube.hpp"

#include <glm/gtc/matrix_transform.hpp>

glr::Application::Application() : vpDrawables( std::vector<Drawable*>() ) {
    sAppName = "OpenGL Application";
}

void glr::Application::OnStart() {
    glViewport( 0, 0, (GLsizei)pWindow->GetWidth(), (GLsizei)pWindow->GetHeight() );

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace( GL_FRONT );
    glDepthFunc(GL_LESS);
    //pQuad = new samples::Quad3D();

    projection_matrix = glm::perspectiveFovLH( 90.0f, (float)(pWindow->GetWidth()), (float)(pWindow->GetHeight()), 0.1f, 100.0f );

    vpDrawables.push_back( new DrawableCube() );
    vpDrawables[0]->position.z = 6.0f;
}

void glr::Application::OnUpdate( const float dt ) {
    glClearColor( 0.2f, 0.1f, 0.2f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if ( pWindow->GetKey( Keys::W ) ) vpDrawables[0]->position.z += 10.0f * dt;
    if ( pWindow->GetKey( Keys::S ) ) vpDrawables[0]->position.z -= 10.0f * dt;
    if ( pWindow->GetKey( Keys::D ) ) vpDrawables[0]->position.x += 10.0f * dt;
    if ( pWindow->GetKey( Keys::A ) ) vpDrawables[0]->position.x -= 10.0f * dt;
    if ( pWindow->GetKey( Keys::Q ) ) vpDrawables[0]->position.y += 10.0f * dt;
    if ( pWindow->GetKey( Keys::E ) ) vpDrawables[0]->position.y -= 10.0f * dt;

    if ( pWindow->GetKey( Keys::I ) ) vpDrawables[0]->rotation.x += 3.0f * dt;
    if ( pWindow->GetKey( Keys::K ) ) vpDrawables[0]->rotation.x -= 3.0f * dt;
    if ( pWindow->GetKey( Keys::L ) ) vpDrawables[0]->rotation.y += 3.0f * dt;
    if ( pWindow->GetKey( Keys::J ) ) vpDrawables[0]->rotation.y -= 3.0f * dt;
    if ( pWindow->GetKey( Keys::U ) ) vpDrawables[0]->rotation.z += 3.0f * dt;
    if ( pWindow->GetKey( Keys::O ) ) vpDrawables[0]->rotation.z -= 3.0f * dt;

    for ( Drawable* pDrawable : vpDrawables ) {

        pDrawable->Draw( projection_matrix );
    }
}

void glr::Application::OnStop() {
    for ( Drawable* pDrawable : vpDrawables ) {

        if ( pDrawable ) delete pDrawable;
    }
}
