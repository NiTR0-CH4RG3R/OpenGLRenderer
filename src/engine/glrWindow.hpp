#ifndef GLR_WINDOW_HPP_INCLUDED
#define GLR_WINDOW_HPP_INCLUDED

#include "glrKeys.hpp"
#include "../third_party/imgui/imgui.h"

#include <GLFW/glfw3.h>

#include <string>

namespace glr {
    class Window {
    public:
        Window( const std::string& name, const uint32_t width, const uint32_t height );
        ~Window();

        void MakeContextCurrent();
        void SwapBuffers();

        static void ProcessMessages();


        void SetWindowResizeCallback( void (*pfOnResize)( uint32_t, uint32_t ) );

        uint32_t GetWidth() const;
        uint32_t GetHeight() const;
        bool IsActive() const;

        bool GetKey( Keys k ) const;

        void ImGuiNewFrame();
        void ImGuiMakeContextCurrent();

    private:
        static void GLFWwindowResizeCallback( GLFWwindow* pWindow, int width, int height );

        GLFWwindow* m_pWindow = nullptr;
        uint32_t m_nWidth = 0;
        uint32_t m_nHeight = 0;

        void (*m_pfOnResize)( uint32_t, uint32_t ) = nullptr;

        ImGuiContext* m_pImGuiContext = nullptr;

    };
}

#endif // GLR_WINDOW_HPP_INCLUDED
