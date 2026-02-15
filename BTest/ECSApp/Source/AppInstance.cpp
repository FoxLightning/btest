// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include "AppInstance.hpp"

#include <cstddef>
#include <iostream>
#include <memory>
#include <print>
#include <string>
#include <vector>

#include "ECSCore/Entity.hpp"

#include "ECSApp/ECSAppAPI.hpp"

#include "ActionManager.hpp"
#include "ActionObject.hpp"
#include "MoveAction.hpp"
#include "ToggleAction.hpp"

namespace ECSApp
{

std::shared_ptr<IECSAppAPI> GetAppInstance()
{
    static std::shared_ptr<IECSAppAPI> appInstance;
    if (!appInstance)
    {
        appInstance = std::make_shared<AppInstance>();
    }
    return appInstance;
}

bool AppInstance::AddEntity(const EntityName& name)
{
    auto [value, result] = entityMap.try_emplace(name.str, std::make_shared<ECSCore::Entity>());
    return result;
}

bool AppInstance::RemoveEntity(const EntityName& name)
{
    const auto entitiesRemoved = entityMap.erase(name.str);
    return entitiesRemoved == 1;
}

bool AppInstance::AddManagerToEntity(const EntityName& entityName, const ManagerType& managerType)
{
    const auto entity = GetEntity(entityName);
    if (!entity)
    {
        return false;
    }

    if (managerType.str == ActionManager::GetManagerTypeName())
    {
        return !entity->CreateManager<ActionManager>().expired();
    }

    return false;
}

bool AppInstance::RemoveManagerFromEntity(const EntityName& entityName, const ManagerType& managerType)
{
    const auto entity = GetEntity(entityName);
    if (!entity)
    {
        std::println(std::cerr, "Entity not found: {}", entityName.str);
        return false;
    }

    if (managerType.str == ActionManager::GetManagerTypeName())
    {
        return entity->DeleteManager<ActionManager>();
    }
    return false;
}

bool AppInstance::SpawnObject(const ObjectType& objectType, const ObjectName& objectName,
                              const std::shared_ptr<ECSCore::Entity>& entity)
{
    if (objectType.str == MoveAction::GetTypeName())
    {
        ECSCore::Object::CreateObject<MoveAction>(entity, objectName, "10 20");
        return true;
    }
    if (objectType.str == ToggleAction::GetTypeName())
    {
        ECSCore::Object::CreateObject<ToggleAction>(entity, objectName, "true");
        return true;
    }
    std::println(std::cerr, "Invalid object type: {}", objectType.str);
    return false;
}

bool AppInstance::AddObjectToEntity(const EntityName& entityName, const ObjectType& objectType,
                                    const ObjectName& objectName)
{
    const auto entity = GetEntity(entityName);
    if (!entity)
    {
        std::println(std::cerr, "Entity not found: {}", entityName.str);
        return false;
    }

    return SpawnObject(objectType, objectName, entity);
}

bool AppInstance::RemoveActionFromEntity(const EntityName& entityName, const ObjectName& actionName)
{
    const auto entity = GetEntity(entityName);
    if (!entity)
    {
        std::println(std::cerr, "Entity not found: {}", entityName.str);
        return false;
    }

    if (const auto actionManager = entity->GetManager<ActionManager>(); !actionManager.expired())
    {
        return actionManager.lock()->RemoveAction(actionName.str);
    }
    std::println(std::cerr, "No action manager to remove action: {}", actionName.str);
    return false;
}

bool AppInstance::GetVisibleActions(const EntityName& entityName, std::vector<std::string>& out)
{
    const auto iterator = entityMap.find(entityName.str);
    if (iterator == entityMap.end())
    {
        std::println(std::cerr, "Entity not found: {}", entityName.str);
        return false;
    }
    const auto entity = iterator->second;

    const auto manager = entity->GetManager<ActionManager>();
    if (manager.expired())
    {
        std::println(std::cerr, "Mo action manager in {} entity.", entityName.str);
        return false;
    }

    const auto visibleActions = manager.lock()->GetVisibleActions();
    for (const auto& action : visibleActions)
    {
        if (action.expired())
        {
            std::println(std::cerr, "Expired action detected");
            continue;
        }

        const auto actionPtr = action.lock();
        if (actionPtr && actionPtr->IsVisible())
        {
            out.push_back(actionPtr->GetName());
        }
    }

    return true;
}

bool AppInstance::GetManagerTypes(std::vector<std::string>& out)
{
    out.emplace_back(ActionManager::GetManagerTypeName());
    return true;
}

bool AppInstance::GetActionTypes(std::vector<std::string>& out)
{
    out.emplace_back(MoveAction::GetTypeName());
    out.emplace_back(ToggleAction::GetTypeName());
    return true;
}

size_t AppInstance::GetEntityCount()
{
    return entityMap.size();
}

std::shared_ptr<ECSCore::Entity> AppInstance::GetEntity(const EntityName& entityName)
{
    const auto iterator = entityMap.find(entityName.str);
    if (iterator == entityMap.end())
    {
        return {};
    }
    return iterator->second;
}

} // namespace ECSApp
