// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include "ECSCore/EntityManager.hpp"

#include <cassert>
#include <functional>
#include <memory>
#include <ranges>
#include <string>

#include <ECSCore/Entity.hpp>

namespace ECSCore
{

std::weak_ptr<Entity> EntityManager::CreateEntity(const std::string& name)
{
    auto [pair, result] = entityMap.emplace(name, std::make_shared<Entity>(name));
    return result ? pair->second : nullptr;
}

bool EntityManager::DeleteEntity(const std::string& name)
{
    const auto deletedCount = entityMap.erase(name);
    assert(deletedCount <= 1);
    return deletedCount > 0;
}

std::weak_ptr<Entity> EntityManager::GetEntity(const std::string& name)
{
    return std::const_pointer_cast<Entity>(static_cast<const EntityManager*>(this)->GetEntity(name).lock());
}

std::weak_ptr<Entity const> EntityManager::GetEntity(const std::string& name) const
{
    const auto iterator = entityMap.find(name);
    return iterator != entityMap.end() ? iterator->second : nullptr;
}

void EntityManager::ForEachEntity(const std::function<void(std::shared_ptr<Entity>)>& function) const
{
    for (const auto& val : entityMap | std::views::values)
    {
        assert(val);
        function(val);
    }
}

} // namespace ECSCore
