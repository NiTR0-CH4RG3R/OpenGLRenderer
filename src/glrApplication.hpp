#ifndef GLRAPPLICATION_HPP_INCLUDED
#define GLRAPPLICATION_HPP_INCLUDED

#include "glrEngine.hpp"
#include "glrDrawable.hpp"

#include <glm/glm.hpp>
#include <vector>


namespace glr {
    class Application : public Engine {
    public:
        Application();

    private:
        void OnStart() override;
        void OnUpdate( const float dt ) override;
        void OnStop() override;

        glm::mat4 projection_matrix;
        std::vector<Drawable*> vpDrawables;
    };
}

#endif // GLRAPPLICATION_HPP_INCLUDED
