#include "glrWindow.hpp"

#include "glrAssert.hpp"
#include "../third_party/glad.h"
#include "../third_party/imgui/imgui_impl_glfw.h"
#include "../third_party/imgui/imgui_impl_opengl3.h"

glr::Window::Window( const std::string& name, const uint32_t width, const uint32_t height ) : m_nWidth( width ), m_nHeight( height ) {
    // Initialize GLFW
    ASSERT_IF_DEBUG( glfwInit() );

    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE ); // Use OpenGL Core Profile
    // Use OpenGL 4.6
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 6 );
    glfwWindowHint( GLFW_RESIZABLE, GLFW_FALSE ); // Make window un-resizable

    // Create the window
    ASSERT_IF_DEBUG( m_pWindow = glfwCreateWindow( m_nWidth, m_nHeight, name.c_str(), nullptr, nullptr ) );

    // Make the gl context current
    MakeContextCurrent();

    ASSERT_IF_DEBUG( gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) );

    glfwSetWindowUserPointer( m_pWindow, reinterpret_cast<void*>(this) );
    glfwSetWindowSizeCallback( m_pWindow, GLFWwindowResizeCallback );


    IMGUI_CHECKVERSION();
    ASSERT_IF_DEBUG( m_pImGuiContext = ImGui::CreateContext() );
    ImGuiMakeContextCurrent();
    ImGui::StyleColorsDark();
    ASSERT_IF_DEBUG( ImGui_ImplGlfw_InitForOpenGL( m_pWindow, true ) );
    ASSERT_IF_DEBUG( ImGui_ImplOpenGL3_Init( "#version 430" ) );
}

glr::Window::~Window() {
    ImGuiMakeContextCurrent();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext( m_pImGuiContext );

    glfwDestroyWindow( m_pWindow );
    glfwTerminate();
}

void glr::Window::MakeContextCurrent() {
    glfwMakeContextCurrent( m_pWindow );
}

void glr::Window::SwapBuffers() {
    glfwSwapBuffers( m_pWindow );
}

void glr::Window::ProcessMessages() {
    glfwPollEvents();
}

void glr::Window::SetWindowResizeCallback( void (*pfOnResize)( uint32_t, uint32_t ) ) {
    m_pfOnResize = pfOnResize;
}

uint32_t glr::Window::GetWidth() const {
    return m_nWidth;
}

uint32_t glr::Window::GetHeight() const {
    return m_nHeight;
}

bool glr::Window::IsActive() const {
    return !glfwWindowShouldClose( m_pWindow );
}

bool glr::Window::GetKey( Keys k ) const {
    return static_cast<bool>( glfwGetKey( m_pWindow, static_cast<int>( k ) ) == GLFW_PRESS );
}


void glr::Window::GLFWwindowResizeCallback( GLFWwindow* pWindow, int width, int height ) {
    Window* pGLRwindow = reinterpret_cast<Window*>( glfwGetWindowUserPointer(pWindow) );
    pGLRwindow->m_nWidth = ( uint32_t ) width;
    pGLRwindow->m_nHeight = ( uint32_t ) height;

    if ( pGLRwindow->m_pfOnResize ) pGLRwindow->m_pfOnResize( pGLRwindow->m_nWidth, pGLRwindow->m_nHeight );
}

void glr::Window::ImGuiMakeContextCurrent() {
    ImGui::SetCurrentContext( m_pImGuiContext );
}

void glr::Window::ImGuiNewFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}
