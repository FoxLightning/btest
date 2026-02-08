// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

namespace ECSCore
{
class Entity;

class EntityManager
{
public:
  EntityManager();
  virtual ~EntityManager();

  std::shared_ptr<Entity> CreateEntity(std::string name);
  bool                    DeleteEntity(std::string name);

  std::shared_ptr<Entity>                     GetEntity(const std::string& name);
  [[nodiscard]] std::shared_ptr<Entity const> GetEntity(const std::string& name) const;

  void ForEachEntity(const std::function<void(Entity&)>& function);
  void ForEachEntity(const std::function<void(Entity const&)>& function) const;

  [[nodiscard]] size_t GetEntityCount() const
  {
    return entityPool.size();
  }

private:
  std::vector<std::shared_ptr<Entity>> entityPool;
  std::unordered_set<std::string>      usedNames;
};

} // namespace ECSCore
