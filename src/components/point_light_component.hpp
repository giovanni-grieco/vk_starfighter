#pragma once

#include "entity.hpp"

namespace engine {
    struct PointLightComponent{
        Entity entity;
        float lightIntensity = 1.f;
    };
}