#pragma once

#include "registry.hpp"

namespace engine
{
    class ISystem
    {
    public:
        virtual ~ISystem() = default;
        virtual void update(Registry &registry, float dt) = 0;
    };
}
