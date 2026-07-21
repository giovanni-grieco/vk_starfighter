#include "system_manager.hpp"

namespace engine
{

    template <typename T, typename... Args>
    std::shared_ptr<T> SystemManager::registerSystem(Args &&...args)
    {
        std::type_index typeName = std::type_index(typeid(T));
        auto system = std::make_shared<T>(std::forward<Args>(args)...);
        m_systems[typeName] = system;
        m_updateOrder.push_back(system); // Deterministic execution order
        return system;
    }

    void SystemManager::updateAll(Registry &registry, float dt)
    {
        for (auto &system : updateOrder)
        {
            system->update(registry, dt);
        }
    }
}