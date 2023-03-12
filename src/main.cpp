#include "OpenGLRenderer.hpp"
#include "MonkeyWithLight/MonkeyWithLight.hpp"

#include <iostream>
#include <string>
#include <cstdio>
#include <unistd.h>

int main( int argc, char* argv[] ) {


    std::string filepath( argv[0] );
    std::string filedir = filepath.substr( 0, filepath.find_last_of( "/\\" ) );
    std::string bindir = filedir.substr( 0, filedir.find_last_of( "/\\" ) );
    std::string rootdir = bindir.substr( 0, bindir.find_last_of( "/\\" ) );
    chdir(rootdir.c_str());

    MonkeyWithLight app;
    if( app.Initialize( 1280, 720 ) ) app.Start();
    app.UnInitialize();
    return 0;
}

//#include "ecs/ecsEntity.hpp"
//#include <iostream>
//
//
//class ComponentA : public ecs::Component {
//public:
//    ComponentA( ecs::Entity* pParent, const int a, const int b ) : ecs::Component( pParent ), a(a), b(b) {
//        std::cout << "Creating ComponentA" << std::endl;
//    };
//
//    ~ComponentA() {
//
//    }
//
//    void OnStart() override {
//        std::cout << "ComponentA::OnStart() has been called!" << std::endl;
//        std::cout << "a = " << a << std::endl;
//        std::cout << "b = " << b << std::endl;
//    }
//
//    void OnUpdate( const float dt ) override {
//        std::cout << "ComponentA::OnUpdate( " << dt << "f ) has been called!" << std::endl;
//    }
//
//    void OnStop() override {
//        std::cout << "ComponentA::OnStop() has been called!" << std::endl;
//    }
//
//private:
//    int a = 0;
//    int b = 0;
//};
//
//
//
//class ComponentB : public ecs::Component {
//public:
//    ComponentB( ecs::Entity* pParent ) : ecs::Component( pParent ) {
//        std::cout << "Creating ComponentA" << std::endl;
//    };
//
//    ~ComponentB() {
//
//    }
//
//    void OnStart() override {
//        std::cout << "ComponentB::OnStart() has been called!" << std::endl;
//
//    }
//
//    void OnUpdate( const float dt ) override {
//        std::cout << "ComponentB::OnUpdate( " << dt << "f ) has been called!" << std::endl;
//    }
//
//    void OnStop() override {
//        std::cout << "ComponentB::OnStop() has been called!" << std::endl;
//    }
//
//private:
//
//};
//
//int main() {
//    ecs::Entity e( nullptr, "sample" );
//    e.AddComponent<ComponentA>( 10, 20 );
//    e["child01"].AddComponent<ComponentB>();
//    e["child02"];e["child03"];
//    e["child01"]["child04"];
//    e.OnStart();
//    e.OnUpdate( 0.2f );
//    e.OnStop();
//
//
//    e.PrintChildrenTree( 0 );
//}
