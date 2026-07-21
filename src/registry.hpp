#pragma once

#include "component_array.hpp"
#include "entity.hpp"

namespace engine
{
    class Registry
    {
    public:
        Entity createEntity();

        void destroyEntity(Entity entity);

        template <typename T>
        void addComponent(Entity entity, T component);

        template <typename T>
        T &getComponent(Entity entity);

        template <typename T>
        bool hasComponent(Entity entity);
    private:
        Entity m_nextEntityId = 0;
        std::vector<Entity> m_freeEntities;
        std::unordered_map<std::type_index, std::shared_ptr<IComponentArray>> m_componentArrays;

        template <typename T>
        std::shared_ptr<ComponentArray<T>> getComponentArray();
    };
}