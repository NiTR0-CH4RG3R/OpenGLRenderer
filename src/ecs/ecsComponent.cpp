#include "ecsComponent.hpp"

ecs::Component::Component( ecs::Entity* pParent ) : m_pParent( pParent ) { };

ecs::Component::~Component() { };

ecs::Entity* ecs::Component::GetParent() {
    return m_pParent;
}
