#include "ecsEntity.hpp"

#include <iostream>

ecs::Entity::Entity( Entity* pParent, const std::string& sName ) : m_pParent( pParent ), m_sName( sName ) { };

ecs::Entity::~Entity() {
    for ( auto& child : m_pChildren ) {
        delete child.second;
    }


    for ( auto& component : m_pComponents ) {
        delete component.second;
    }

    m_pChildren.clear();
    m_pComponents.clear();
}

void ecs::Entity::OnStart() {
    for ( auto& component : m_pComponents ) {
        component.second->OnStart();
    }

    for ( auto& child : m_pChildren ) {
        child.second->OnStart();
    }
}

void ecs::Entity::OnUpdate( const float dt ) {
    for ( auto& component : m_pComponents ) {
        component.second->OnUpdate( dt );
    }

    for ( auto& child : m_pChildren ) {
        child.second->OnUpdate( dt );
    }
}

void ecs::Entity::OnStop() {
    for ( auto& component : m_pComponents ) {
        component.second->OnStop();
    }

    for ( auto& child : m_pChildren ) {
        child.second->OnStop();
    }
}

ecs::Entity* ecs::Entity::GetParent() {
    return m_pParent;
}

ecs::Entity* ecs::Entity::AddChild( const std::string& name ) {
    //Check if there's already a child by given name
    Entity* pChild = GetChild( name );

    //A component exists
    if (pChild) {
        return pChild;
    }

    //Add the new component to the map
    pChild = new Entity( this, name );
    m_pChildren.insert( { name, pChild });
    return pChild;
}

ecs::Entity* ecs::Entity::GetChild( const std::string& name ) {
    auto it = m_pChildren.find(name);

    if (it == m_pChildren.end()) {
        //There's no component by the given name
        return nullptr;
    }

    //Otherwise return the pointer to the component
    return it->second;
}

void ecs::Entity::PrintChildrenTree( int tabs ) {
    for ( int i = 0; i < tabs ; i++ ) {

        std::cout << "\t";
    }

    std::cout << m_sName << std::endl;

    for ( auto& child : m_pChildren ) {
        child.second->PrintChildrenTree( tabs + 1 );
    }
}

ecs::Entity& ecs::Entity::operator[] (const std::string& name) {
    return (*AddChild( name ));
}
