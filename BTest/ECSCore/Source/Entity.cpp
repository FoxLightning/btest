// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include "ECSCore/Entity.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <memory>
#include <print>
#include <ranges>

#include "ECSCore/ObjectManager.hpp"

namespace ECSCore
{

void Entity::AttachObjectToEntity(const std::weak_ptr<Object>& object)
{
    int32_t ownerCount = 0;
    for (const auto& manager : groupToManagerMap | std::ranges::views::values)
    {
        if (const bool isOwner = manager->TryAttachObjectToComponent(object); isOwner)
        {
            ++ownerCount;
        }
    }
    if (ownerCount == 0)
    {
        std::println(std::cerr, "No owners for entity");
        assert(false);
    }
    if (ownerCount > 1)
    {
        std::println(std::cerr, "Multiple owners for entity");
        assert(false);
    }
}

void Entity::DetachObjectFromEntity()
{
    for (const auto& manager : groupToManagerMap | std::ranges::views::values)
    {
        manager->EraseExpiredWeakPointers();
    }
}

} // namespace ECSCore
