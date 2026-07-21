#include <vector>
#include <unordered_map>
#include <memory>
#include <typeindex>

#include "entity.hpp"
#include "component_array.hpp"

namespace engine
{
    template <typename T>       
    void ComponentArray<T>::insert(Entity entity, T component)
    {
        assert(m_entityToData.size() <= entity && "Entity out of range");
        assert(!has(entity) && "Component added to same entity more than once.");

        // Put new entry at end and update the maps
        size_t newIndex = m_data.size();
        if (m_entityToData.size() <= entity) {
            m_entityToData.resize(entity + 1, -1);
        }
        m_entityToData[entity] = newIndex;
        m_dataToEntity.push_back(entity);
        m_data.push_back(component);
    }

    template <typename T>
    T &ComponentArray<T>::get(Entity entity){
        return m_data[m_entityToData[entity]];
    }

    template <typename T>
    bool ComponentArray<T>::has(Entity entity) const{
        return entity < m_entityToData.size() && m_entityToData[entity] != -1;
    }

    template <typename T>
    void ComponentArray<T>::entityDestroyed(Entity entity){
        if (!has(entity)) return;

        // Move last element into deleted slot to keep array dense
        int indexToRemove = m_entityToData[entity];
        int lastIndex = static_cast<int>(m_data.size() - 1);
        
        m_data[indexToRemove] = m_data[lastIndex];

        Entity entityOfLastElement = m_dataToEntity[lastIndex];
        m_entityToData[entityOfLastElement] = indexToRemove;
        m_dataToEntity[indexToRemove] = entityOfLastElement;

        m_entityToData[entity] = -1;
        m_data.pop_back();
        m_dataToEntity.pop_back();
    }
}