// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once
#include <memory>
#include <string>
#include <type_traits>
#include <typeindex>
#include <unordered_map>

#include "Object.hpp"

namespace ECSCore
{
class ObjectManager;

class Entity : public std::enable_shared_from_this<Entity>
{
  public:
    Entity()                         = delete;
    Entity(const Entity&)            = delete;
    Entity(Entity&&)                 = delete;
    Entity& operator=(const Entity&) = delete;
    Entity& operator=(Entity&&)      = delete;

    explicit Entity(std::string inName);
    virtual ~Entity() = default;

    [[nodiscard]] std::string GetName() const;

    template<typename ManagerType>
    std::weak_ptr<ManagerType> CreateManager();

    template<typename ManagerType>
    bool DeleteManager();

    template<typename ManagerType>
    [[nodiscard]] std::weak_ptr<ManagerType> GetManager();

    template<typename ManagerType>
    [[nodiscard]] std::weak_ptr<ManagerType> GetManager() const;

    [[nodiscard]] size_t GetManagersNum() const
    {
        return groupToManagerMap.size();
    }

  private:
    std::unordered_map<std::type_index, std::shared_ptr<ObjectManager>> groupToManagerMap;

    const std::string name;
};

template<typename ManagerType>
std::weak_ptr<ManagerType> Entity::CreateManager()
{
    using NonConstManager = std::remove_const_t<ManagerType>;
    static_assert(std::is_base_of_v<ObjectManager, NonConstManager>);
    auto [objectManager, bSuccess] = groupToManagerMap.emplace(std::type_index(typeid(NonConstManager)),
                                                               std::make_shared<NonConstManager>(shared_from_this()));
    if (bSuccess)
    {
        return std::static_pointer_cast<NonConstManager>(objectManager->second);
    }
    return {};
}

template<typename ManagerType>
bool Entity::DeleteManager()
{
    using NonConstManager = std::remove_const_t<ManagerType>;
    static_assert(std::is_base_of_v<ObjectManager, NonConstManager>);
    return groupToManagerMap.erase(std::type_index(typeid(NonConstManager))) == 1;
}

template<typename ManagerType>
std::weak_ptr<ManagerType> Entity::GetManager()
{
    using NonConstManager = std::remove_const_t<ManagerType>;
    const auto* constThis = static_cast<const Entity*>(this);
    return std::const_pointer_cast<NonConstManager>(constThis->GetManager<NonConstManager>().lock());
}

template<typename ManagerType>
std::weak_ptr<ManagerType> Entity::GetManager() const
{
    using NonConstManager = std::remove_const_t<ManagerType>;
    static_assert(std::is_base_of_v<ObjectManager, NonConstManager>);
    const auto itr = groupToManagerMap.find(std::type_index(typeid(NonConstManager)));
    return itr != groupToManagerMap.end() ? std::static_pointer_cast<const NonConstManager>(itr->second)
                                          : std::weak_ptr<const NonConstManager>();
}

} // namespace ECSCore
