// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include "ECSCore/ObjectManager.hpp"

#include <algorithm>
#include <cstdint>
#include <functional>
#include <memory>
#include <utility>

#include "ECSCore/Object.hpp"

namespace ECSCore
{

int32_t ObjectManager::EraseObjectsIf(const std::function<bool(std::shared_ptr<Object>)>& predicate)
{
    return static_cast<int32_t>(std::erase_if(objectPool, predicate));
}

std::weak_ptr<Object> ObjectManager::GetObject(const std::function<bool(std::shared_ptr<Object>)>& predicate)
{
    const std::weak_ptr constWeak = std::as_const(*this).GetObject(predicate);

    if (const std::shared_ptr sharedWeak = constWeak.lock())
    {
        return std::weak_ptr{std::const_pointer_cast<Object>(sharedWeak)};
    }

    return {};
}

std::weak_ptr<const Object> ObjectManager::GetObject(
    const std::function<bool(std::shared_ptr<Object>)>& predicate) const
{
    const auto iterator = std::ranges::find_if(objectPool, predicate);
    return iterator != objectPool.end() ? std::weak_ptr<const Object>{*iterator} : std::weak_ptr<const Object>{};
}

void ObjectManager::ForEachObject(const std::function<void(std::shared_ptr<Object>)>& function) const
{
    std::ranges::for_each(objectPool, function);
}

} // namespace ECSCore
