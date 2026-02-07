#pragma once

#include "ECSApp/CLI.hpp"

namespace ecsapp
{
std::shared_ptr<IECSAPI> GetAppInstance();

class AppInstance : public IECSAPI
{
public:
    AppInstance();
    ~AppInstance() override;

    bool AddEntity(std::string Name) override;
    bool RemoveEntity(std::string Name) override;
    bool AddComponent(std::string EntityName, std::string ComponentType, std::string ComponentName) override;
    bool RemoveComponent(std::string EntityName, std::string ComponentType, std::string ComponentName) override;
    bool GetVisibleComponents(std::string EntityName, std::vector<std::string>& OutVisibleEntities) override;
};

} // namespace ecsapp
