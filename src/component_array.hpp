#include <vector>
#include <unordered_map>
#include <memory>
#include <typeindex>

#include "entity.hpp"

namespace engine
{

    // --- Base Component Array Interface ---
    class IComponentArray
    {
    public:
        virtual ~IComponentArray() = default;
        virtual void entityDestroyed(Entity entity) = 0;
    };

    // --- Templated Array (Contiguous Memory per Component Type) ---
    template <typename T>
    class ComponentArray : public IComponentArray
    {
    public:
        void insert(Entity entity, T component);

        T &get(Entity entity);

        bool has(Entity entity) const;

        void entityDestroyed(Entity entity) override;

    private:
        std::vector<T> m_data;              // Packed component data
        std::vector<int> m_entityToData;    // Sparse map: Entity -> Index
        std::vector<Entity> m_dataToEntity; // Dense map: Index -> Entity
    };
}