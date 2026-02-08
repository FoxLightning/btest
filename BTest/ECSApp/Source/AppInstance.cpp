#include "AppInstance.hpp"

#include <iostream>

namespace ecsapp
{

AppInstance::AppInstance()
{
    std::cout << "App instance created\n";
}

AppInstance::~AppInstance()
{
    std::cout << "App instance destroyed\n";
}

std::shared_ptr<IECSAPI> GetAppInstance()
{
    static std::shared_ptr<IECSAPI> appInstance;
    if (!appInstance)
    {
        appInstance = std::make_shared<AppInstance>();
    }
    return appInstance;
}

bool AppInstance::AddEntity(std::string Name)
{
    std::cout << "Add entity" << Name << "\n";
    return true;
}

bool AppInstance::RemoveEntity(std::string Name)
{
    std::cout << "Remove entity: " << Name << "\n";
    return true;
}

bool AppInstance::AddComponent(std::string EntityName, std::string ComponentType, std::string ComponentName)
{
    std::cout << std::format("Add component {} to entity {} of type {}", ComponentName, EntityName, ComponentType);
    return true;
}

bool AppInstance::RemoveComponent(std::string EntityName, std::string ComponentType, std::string ComponentName)
{
    std::cout << std::format("Remove component {} from entity {} of type {}", ComponentName, EntityName, ComponentType);
    return true;
}

bool AppInstance::GetVisibleComponents(std::string EntityName, std::vector<std::string>& OutVisibleEntities)
{
    std::cout << "Get visible components for entity: " << EntityName << "\n";
    return true;
}

size_t AppInstance::GetEntityCount()
{
    return 0;
}
} // namespace ecsapp