#ifndef ECSENTITY_HPP_INCLUDED
#define ECSENTITY_HPP_INCLUDED

#include "ecsComponent.hpp"

#include <string>
#include <unordered_map>
#include <typeinfo>
#include <type_traits>

namespace ecs {
    class Entity {
    public:
        Entity( Entity* pParent, const std::string& sName );
        ~Entity();

        void OnStart();
        void OnUpdate( const float dt );
        void OnStop();

        Entity* GetParent();

        Entity* AddChild( const std::string& name );
        Entity* GetChild( const std::string& name );

        template<class T, class... _Types>
        T* AddComponent(_Types&&... args) {
            //Check if the T is a derrived class of the componet class
            static_assert(std::is_base_of<Component, T>::value, "T must inherit from CrappyComponent class");


            //Check if there's already a child by given name
            T* pComponent = static_cast<T*>(GetComponent<T>());

            //A component exists
            if (pComponent) {
                return pComponent;
            }

            //Add the new component to the map
            pComponent = new T(this, std::forward<_Types>(args)...);
            m_pComponents.insert({ typeid(T).hash_code(), pComponent });
            return pComponent;
        }

        template<class T>
        T* GetComponent() {
            //Check if the T is a derrived class of the componet class
            static_assert(std::is_base_of<Component, T>::value, "T must inherit from CrappyComponent class");

            auto it = m_pComponents.find(typeid(T).hash_code());

            if (it == m_pComponents.end()) {
                //There's no component by the given name
                return nullptr;
            }

            //Otherwise return the pointer to the component
            return static_cast<T*>(it->second);
        }

        template<class T, class... _Types>
        T& operator[] (_Types&&... args) {
            return *(AddComponent<T>(args...));
        }

        void PrintChildrenTree( int tabs );

        Entity& operator[] (const std::string& name);

    private:
        Entity* m_pParent = nullptr;
        std::string m_sName = "";

        std::unordered_map<std::string, Entity*> m_pChildren;
        std::unordered_map<size_t, Component*> m_pComponents;
    };
}

#endif // ECSENTITY_HPP_INCLUDED
