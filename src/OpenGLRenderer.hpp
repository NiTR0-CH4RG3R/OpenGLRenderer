#ifndef OPENGLRENDERER_HPP_INCLUDED
#define OPENGLRENDERER_HPP_INCLUDED

#include "engine/glrEngine.hpp"
#include "Drawable.hpp"

#include <glm/glm.hpp>
#include <vector>

class OpenGLRenderer : public glr::Engine {
public:
    OpenGLRenderer();

private:
    void OnStart() override;
    void OnUpdate( const float dt ) override;
    void OnStop() override;

    glm::mat4 projection_matrix;
    std::vector<Drawable*> vpDrawables;
};

#endif // OPENGLRENDERER_HPP_INCLUDED
