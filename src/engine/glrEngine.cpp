#include "glrEngine.hpp"
#include "../third_party/imgui/imgui_impl_opengl3.h"

bool glr::Engine::Initialize( const uint32_t width, const uint32_t height ) {
    pWindow = new Window( sAppName, width, height );
    pIO = &( ImGui::GetIO() ); (void)(*pIO);
    return !( pWindow == nullptr );
}

void glr::Engine::UnInitialize() {
    delete pWindow;
}

void glr::Engine::Start() {
    double fCurrentTime = glfwGetTime();
    double fPreviousTime = fCurrentTime;

    OnStart();
    while( pWindow->IsActive() ) {
        glr::Window::ProcessMessages();
        pWindow->ImGuiNewFrame();


        fCurrentTime = glfwGetTime();
        double dt = fCurrentTime - fPreviousTime;
        fPreviousTime = fCurrentTime;

        OnUpdate( dt );

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        pWindow->SwapBuffers();
    }
    OnStop();
}
