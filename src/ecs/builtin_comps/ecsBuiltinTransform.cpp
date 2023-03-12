#include "ecsBuiltinTransform.hpp"
#include "../ecsEntity.hpp"
#include <glm/gtc/matrix_transform.hpp>

ecs::builtin_comps::Transform::Transform(  Entity* pParent, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale ) : ecs::Component(pParent), local_position( position ), local_rotation( rotation ), local_scale( scale ) {

}

ecs::builtin_comps::Transform::~Transform() {

}

void ecs::builtin_comps::Transform::OnStart() {
    UpdateGloabalTransformationMatrix();
}

void ecs::builtin_comps::Transform::OnUpdate( const float dt ) {
    UpdateGloabalTransformationMatrix();
}

void ecs::builtin_comps::Transform::OnStop() {

}

void ecs::builtin_comps::Transform::UpdateGloabalTransformationMatrix() {
    global_transformation = glm::translate( GetParent()->GetComponent<Transform>()->global_transformation, local_position );
    global_transformation = glm::rotate( global_transformation, local_rotation.y, glm::vec3( 0.0f, 1.0f, 0.0f ) );
    global_transformation = glm::rotate( global_transformation, local_rotation.x, glm::vec3( 1.0f, 0.0f, 0.0f ) );
    global_transformation = glm::rotate( global_transformation, local_rotation.z, glm::vec3( 0.0f, 0.0f, 1.0f ) );
    global_transformation = glm::scale( global_transformation, local_scale );
}


