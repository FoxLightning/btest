// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once

#include <cstddef>
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
    Entity(const Entity&)            = delete;
    Entity(Entity&&)                 = delete;
    Entity& operator=(const Entity&) = delete;
    Entity& operator=(Entity&&)      = delete;

    explicit Entity() = default;
    virtual ~Entity() = default;

    template<class tManagerType, class... tArgs>
    std::weak_ptr<tManagerType> CreateManager(tArgs... args);

    template<typename tManagerType>
    bool DeleteManager();

    template<typename tManagerType>
    [[nodiscard]] std::weak_ptr<tManagerType> GetManager();

    template<typename tManagerType>
    [[nodiscard]] std::weak_ptr<tManagerType> GetManager() const;

    [[nodiscard]] size_t GetManagersNum() const
    {
        return groupToManagerMap.size();
    }

  private:
    std::unordered_map<std::type_index, std::shared_ptr<ObjectManager>> groupToManagerMap;
};

template<typename tManagerType, typename... tArgs>
std::weak_ptr<tManagerType> Entity::CreateManager(tArgs... args)
{
    using NonConstManager = std::remove_const_t<tManagerType>;
    static_assert(std::is_base_of_v<ObjectManager, NonConstManager>);
    auto [objectManager, bSuccess] = groupToManagerMap.emplace(
        std::type_index(typeid(NonConstManager)), std::make_shared<NonConstManager>(args...));
    if (bSuccess)
    {
        return std::static_pointer_cast<NonConstManager>(objectManager->second);
    }
    return {};
}

template<typename tManagerType>
bool Entity::DeleteManager()
{
    using NonConstManager = std::remove_const_t<tManagerType>;
    static_assert(std::is_base_of_v<ObjectManager, NonConstManager>);
    return groupToManagerMap.erase(std::type_index(typeid(NonConstManager))) == 1;
}

template<typename tManagerType>
std::weak_ptr<tManagerType> Entity::GetManager()
{
    using NonConstManager = std::remove_const_t<tManagerType>;
    const auto* constThis = static_cast<const Entity*>(this);
    return std::const_pointer_cast<NonConstManager>(constThis->GetManager<NonConstManager>().lock());
}

template<typename tManagerType>
std::weak_ptr<tManagerType> Entity::GetManager() const
{
    using tNonConstManager = std::remove_const_t<tManagerType>;
    static_assert(std::is_base_of_v<ObjectManager, tNonConstManager>);
    const auto itr = groupToManagerMap.find(std::type_index(typeid(tNonConstManager)));
    return itr != groupToManagerMap.end() ? std::static_pointer_cast<const tNonConstManager>(itr->second)
                                          : std::weak_ptr<const tNonConstManager>();
}

} // namespace ECSCore
