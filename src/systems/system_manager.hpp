#pragma once

#include "system.hpp"
#include <unordered_map>
#include <vector>
#include <memory>
#include <typeindex>

namespace engine
{
    class SystemManager
    {
    public:
        template <typename T, typename... Args>
        std::shared_ptr<T> registerSystem(Args &&...args);

        void updateAll(Registry &registry, float dt);

    private:
        std::unordered_map<std::type_index, std::unique_ptr<ISystem>> systems;
        std::vector<std::shared_ptr<ISystem>> updateOrder;
    };
}