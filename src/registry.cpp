#include "registry.hpp"

namespace engine
{

    Entity Registry::createEntity()
    {
        Entity id;
        if (!m_freeEntities.empty())
        {
            id = m_freeEntities.back();
            m_freeEntities.pop_back();
        }
        else
        {
            id = m_nextEntityId++;
        }
        return id;
    }

    void Registry::destroyEntity(Entity entity)
    {
        for (auto &[type, array] : m_componentArrays)
        {
            array->entityDestroyed(entity);
        }
        m_freeEntities.push_back(entity);
    }

    template <typename T>
    void Registry::addComponent(Entity entity, T component)
    {
        getComponentArray<T>()->insert(entity, component);
    }

    template <typename T>
    T &Registry::getComponent(Entity entity)
    {
        return getComponentArray<T>()->get(entity);
    }

    template <typename T>
    bool Registry::hasComponent(Entity entity)
    {
        return getComponentArray<T>()->has(entity);
    }

    template <typename T>
    std::shared_ptr<ComponentArray<T>> getComponentArray()
    {
        std::type_index typeName = std::type_index(typeid(T));
        if (m_componentArrays.find(typeName) == m_componentArrays.end())
        {
            m_componentArrays[typeName] = std::make_shared<ComponentArray<T>>();
        }
        return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
    }

}