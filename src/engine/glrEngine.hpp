#ifndef GLRENGINE_HPP_INCLUDED
#define GLRENGINE_HPP_INCLUDED

#include "glrWindow.hpp"

#include <string>

namespace glr {
    class Engine {
    public:
        bool Initialize( const uint32_t width, const uint32_t height );
        void UnInitialize();
        void Start();

    protected:
        virtual void OnStart() = 0;
        virtual void OnUpdate( const float dt ) = 0;
        virtual void OnStop() = 0;

        Window* pWindow = nullptr;
        std::string sAppName = "OpenGL Renderer";

        ImGuiIO* pIO = nullptr;
    };
}

#endif // GLRENGINE_HPP_INCLUDED
