// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include "ECSCore/Entity.hpp"

#include <memory>
#include <ranges>

#include "ECSCore/ObjectManager.hpp"

namespace ECSCore
{

void Entity::AttachObjectToEntity(const std::weak_ptr<Object>& object)
{
    for (const auto& manager : groupToManagerMap | std::ranges::views::values)
    {
        manager->TryAttachObjectToComponent(object);
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
