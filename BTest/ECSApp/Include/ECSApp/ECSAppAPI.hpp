// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

namespace ECSApp
{

struct ManagerType
{
    std::string str;
};

struct ObjectType
{
    std::string str;
};

struct ObjectName
{
    std::string str;
};

struct EntityName
{
    std::string str;
};

class IECSAppAPI
{
  public:
    virtual ~IECSAppAPI()                             = default;
    virtual bool AddEntity(const EntityName& name)    = 0;
    virtual bool RemoveEntity(const EntityName& name) = 0;

    virtual bool AddManagerToEntity(const EntityName& entityName, const ManagerType& managerType)      = 0;
    virtual bool RemoveManagerFromEntity(const EntityName& entityName, const ManagerType& managerType) = 0;

    virtual bool AddObjectToEntity(const EntityName& entityName, const ObjectType& objectType,
                                   const ObjectName& objectName)                                    = 0;
    virtual bool RemoveActionFromEntity(const EntityName& entityName, const ObjectName& actionName) = 0;

    virtual bool GetVisibleActions(const EntityName& entityName, std::vector<std::string>& out) = 0;

    virtual size_t GetEntityCount() = 0;
};

std::shared_ptr<IECSAppAPI> GetAppInstance();

} // namespace ECSApp
