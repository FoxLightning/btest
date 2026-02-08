// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

namespace ECSCore
{
class Entity;

class EntityManager
{
public:
    EntityManager(const EntityManager&)            = delete;
    EntityManager(EntityManager&&)                 = delete;
    EntityManager& operator=(const EntityManager&) = delete;
    EntityManager& operator=(EntityManager&&)      = delete;

    EntityManager()          = default;
    virtual ~EntityManager() = default;

    std::weak_ptr<Entity> CreateEntity(const std::string& name);
    bool                    DeleteEntity(const std::string& name);

    [[nodiscard]] std::weak_ptr<Entity>       GetEntity(const std::string& name);
    [[nodiscard]] std::weak_ptr<Entity const> GetEntity(const std::string& name) const;

    void ForEachEntity(const std::function<void(std::shared_ptr<Entity>)>& function) const;

    [[nodiscard]] size_t GetEntityCount() const
    {
        return entityMap.size();
    }

  private:
    // Entity name to entity ptr
    std::unordered_map<std::string, std::shared_ptr<Entity>> entityMap;
};

} // namespace ECSCore
