#ifndef ECSCOMPONENT_HPP_INCLUDED
#define ECSCOMPONENT_HPP_INCLUDED

namespace ecs {

    class Entity;

    class Component {
    public:
        Component( Entity* pParent );
        virtual ~Component();

        virtual void OnStart() = 0;
        virtual void OnUpdate( const float dt ) = 0;
        virtual void OnStop() = 0;

    protected:
        Entity* GetParent();

    private:
        Entity* m_pParent = nullptr;
    };
}

#endif // ECSCOMPONENT_HPP_INCLUDED
