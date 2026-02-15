// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "ECSApp/ECSAppAPI.hpp"

namespace ECSCore
{
class Entity;
}

namespace ECSApp
{
std::shared_ptr<IECSAppAPI> GetAppInstance();

class AppInstance : public IECSAppAPI
{
  public:
    AppInstance()           = default;
    ~AppInstance() override = default;

    bool AddEntity(const EntityName& name) override;
    bool RemoveEntity(const EntityName& name) override;

    bool AddManagerToEntity(const EntityName& entityName, const ManagerType& managerType) override;
    bool RemoveManagerFromEntity(const EntityName& entityName, const ManagerType& managerType) override;

    bool AddObjectToEntity(const EntityName& entityName, const ObjectType& objectType, const ObjectName& objectName) override;
    bool RemoveActionFromEntity(const EntityName& entityName, const ObjectName& actionName) override;

    bool GetVisibleActions(const EntityName& entityName, std::vector<std::string>& out) override;

    bool GetManagerTypes(std::vector<std::string>& out) override;
    bool GetActionTypes(std::vector<std::string>& out) override;

    size_t GetEntityCount() override;

  private:
    static bool                      SpawnObject(const ObjectType& objectType, const ObjectName& objectName,
                                                 const std::shared_ptr<ECSCore::Entity>& entity);
    std::shared_ptr<ECSCore::Entity> GetEntity(const EntityName& entityName);
    std::unordered_map<std::string, std::shared_ptr<ECSCore::Entity>> entityMap;
};

} // namespace ECSApp
