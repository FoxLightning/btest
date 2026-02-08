// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include "ECSCore/Object.hpp"

#include <cassert>
#include <cstdint>
#include <string>

namespace ECSCore
{
EObjectType GetObjectName(const std::string& name)
{
    for (int32_t i = 0; i < GObjectTypeNames.size(); ++i)
    {
        if (name == GObjectTypeNames[i])
        {
            return static_cast<EObjectType>(i);
        }
    }
    assert(false);
    return EObjectType::Null;
}

EObjectType Object::GetObjectType() const
{
    return EObjectType::Null;
}
} // namespace ECSCore
