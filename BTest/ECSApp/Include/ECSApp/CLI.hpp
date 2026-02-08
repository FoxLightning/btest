#pragma once

#include <memory>
#include <string>
#include <vector>

namespace ecsapp
{

class IECSAPI
{
  public:
    virtual ~IECSAPI()                                                                                        = default;
    virtual bool   AddEntity(std::string Name)                                                                = 0;
    virtual bool   RemoveEntity(std::string Name)                                                             = 0;
    virtual bool   AddComponent(std::string EntityName, std::string ComponentType, std::string ComponentName) = 0;
    virtual bool   RemoveComponent(std::string EntityName, std::string ComponentType, std::string ComponentName) = 0;
    virtual bool   GetVisibleComponents(std::string EntityName, std::vector<std::string>& OutVisibleEntities)    = 0;
    virtual size_t GetEntityCount()                                                                              = 0;
};

std::shared_ptr<IECSAPI> GetAppInstance();

} // namespace ecsapp
