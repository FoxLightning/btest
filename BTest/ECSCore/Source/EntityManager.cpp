// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include "ECSCore/EntityManager.hpp"
#include <ECSCore/Entity.hpp>
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <memory>
#include <string>
#include <utility>

namespace ECSCore
{

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

std::shared_ptr<Entity> EntityManager::CreateEntity(std::string name)
{
    if (usedNames.contains(name))
    {
        return GetEntity(name);
    }
    return entityPool.emplace_back(std::make_shared<Entity>(std::move(name)));
}

bool EntityManager::DeleteEntity(std::string name)
{
    const size_t deletedCount{std::erase_if(entityPool, [&name](const std::shared_ptr<Entity>& entity)
                                            { return entity->GetName() == name; })};
    assert(deletedCount <= 1);
    return deletedCount > 0;
}

std::shared_ptr<Entity> EntityManager::GetEntity(const std::string& name)
{
    return std::const_pointer_cast<Entity>(static_cast<const EntityManager*>(this)->GetEntity(name));
}

std::shared_ptr<Entity const> EntityManager::GetEntity(const std::string& name) const
{
    const auto iterator = std::ranges::find_if(entityPool, [&name](const std::shared_ptr<Entity>& entity)
                                               { return entity->GetName() == name; });
    return iterator != entityPool.end() ? *iterator : nullptr;
}

void EntityManager::ForEachEntity(const std::function<void(Entity&)>& function)
{
    for (auto& entity : entityPool)
    {
        function(*entity);
    }
}

void EntityManager::ForEachEntity(const std::function<void(Entity const&)>& function) const
{
    for (const auto& entity : entityPool)
    {
        function(*entity);
    }
}

} // namespace ECSCore
