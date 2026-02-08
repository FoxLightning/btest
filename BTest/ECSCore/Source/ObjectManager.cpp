// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include "ECSCore/ObjectManager.hpp"

#include <cassert>
#include <functional>
#include <memory>
#include <ranges>
#include <string>

#include "ECSCore/Object.hpp"

namespace ECSCore
{

bool ObjectManager::DeleteObject(const std::string& inName)
{
    return objectPool.erase(inName) == 1;
}

std::weak_ptr<Object> ObjectManager::GetObject(const std::string& inName)
{
    return std::const_pointer_cast<Object>(static_cast<const ObjectManager*>(this)->GetObject(inName).lock());
}

std::weak_ptr<const Object> ObjectManager::GetObject(const std::string& inName) const
{
    if (const auto itr = objectPool.find(inName); itr != objectPool.end())
    {
        return itr->second;
    }
    return {};
}

void ObjectManager::ForEachObject(const std::function<void(std::weak_ptr<Object>)>& function) const
{
    for (const auto& objectPtr : objectPool | std::views::values)
    {
        assert(objectPtr);
        function(objectPtr);
    }
}

} // namespace ECSCore
