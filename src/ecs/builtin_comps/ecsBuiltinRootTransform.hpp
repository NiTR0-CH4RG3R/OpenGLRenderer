#ifndef ECSBUILTINROOTTRANSFORM_HPP_INCLUDED
#define ECSBUILTINROOTTRANSFORM_HPP_INCLUDED

#include "ecsBuiltinTransform.hpp"

namespace ecs {
    namespace builtin_comps {
        class RootTransform : public Transform {
        public:
            RootTransform( Entity* pEntity );
            ~RootTransform();

            void OnStart() override;
            void OnUpdate( const float dt ) override;
            void OnStop() override;

        private:
            void UpdateGloabalTransformationMatrix() override;
        };
    }
}

#endif // ECSBUILTINROOTTRANSFORM_HPP_INCLUDED
