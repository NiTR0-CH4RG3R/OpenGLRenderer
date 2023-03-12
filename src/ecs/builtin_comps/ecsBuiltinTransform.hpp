#ifndef ECSBUILTINTRANSFORM_HPP_INCLUDED
#define ECSBUILTINTRANSFORM_HPP_INCLUDED

#include "../ecsComponent.hpp"
#include <glm/glm.hpp>

namespace ecs {
    namespace builtin_comps {
        class Transform : public Component {
        public:
            Transform( Entity* pParent, const glm::vec3& position = glm::vec3( 0.0f, 0.0f, 0.0f ), const glm::vec3& rotation = glm::vec3( 0.0f, 0.0f, 0.0f ), const glm::vec3& scale = glm::vec3( 0.0f, 0.0f, 0.0f ) );
            ~Transform();

            virtual void OnStart() override;
            virtual void OnUpdate( const float dt ) override;
            virtual void OnStop() override;

            glm::vec3 local_position;
            glm::vec3 local_rotation;
            glm::vec3 local_scale;

        protected:
            virtual void UpdateGloabalTransformationMatrix();
            glm::mat4 global_transformation;
        };
    }
}

#endif // ECSBUILTINTRANSFORM_HPP_INCLUDED
