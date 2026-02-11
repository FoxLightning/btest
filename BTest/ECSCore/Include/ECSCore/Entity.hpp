// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once

#include <cstddef>
#include <memory>
#include <type_traits>
#include <typeindex>
#include <unordered_map>

namespace ECSCore
{
class IObjectManager;
class Object;

class Entity
{
  public:
    Entity(const Entity&)            = delete;
    Entity(Entity&&)                 = delete;
    Entity& operator=(const Entity&) = delete;
    Entity& operator=(Entity&&)      = delete;

    explicit Entity() = default;
    virtual ~Entity() = default;

    void AttachObjectToEntity(const std::weak_ptr<Object>& object);
    void DetachObjectFromEntity();

    template<class tManagerType, class... tArgs>
    std::weak_ptr<tManagerType> CreateManager(tArgs&&... args);

    template<typename tManagerType>
    bool DeleteManager();

    template<typename tManagerType>
    [[nodiscard]] std::weak_ptr<tManagerType> GetManager();

    template<typename tManagerType>
    [[nodiscard]] std::weak_ptr<const tManagerType> GetManager() const;

    [[nodiscard]] size_t GetManagersNum() const
    {
        return groupToManagerMap.size();
    }

  private:
    std::unordered_map<std::type_index, std::shared_ptr<IObjectManager>> groupToManagerMap;
};

template<typename tManagerType, typename... tArgs>
std::weak_ptr<tManagerType> Entity::CreateManager(tArgs&&... args)
{
    using tCleanManagerType = std::remove_cvref_t<tManagerType>;
    static_assert(std::is_base_of_v<IObjectManager, tCleanManagerType>);
    auto [objectManager, bSuccess] = groupToManagerMap.emplace(
        std::type_index(typeid(tCleanManagerType)), std::make_shared<tCleanManagerType>(std::forward<tArgs>(args)...));
    if (bSuccess)
    {
        return std::static_pointer_cast<tManagerType>(objectManager->second);
    }
    return {};
}

template<typename tManagerType>
bool Entity::DeleteManager()
{
    using tCleanManagerType = std::remove_cvref_t<tManagerType>;
    static_assert(std::is_base_of_v<IObjectManager, tCleanManagerType>);

    static_assert(std::is_base_of_v<IObjectManager, tCleanManagerType>);
    return groupToManagerMap.erase(std::type_index(typeid(tCleanManagerType))) == 1;
}

template<typename tManagerType>
std::weak_ptr<tManagerType> Entity::GetManager()
{
    using tCleanManagerType = std::remove_cvref_t<tManagerType>;
    static_assert(std::is_base_of_v<IObjectManager, tCleanManagerType>);

    const auto* constThis = static_cast<const Entity*>(this);
    return std::const_pointer_cast<tManagerType>(constThis->GetManager<tCleanManagerType>().lock());
}

template<typename tManagerType>
std::weak_ptr<const tManagerType> Entity::GetManager() const
{
    using tCleanManagerType = std::remove_cvref_t<tManagerType>;
    static_assert(std::is_base_of_v<IObjectManager, tCleanManagerType>);

    const auto itr = groupToManagerMap.find(std::type_index(typeid(tCleanManagerType)));
    return itr != groupToManagerMap.end() ? std::static_pointer_cast<const tCleanManagerType>(itr->second)
                                          : std::weak_ptr<const tCleanManagerType>();
}

} // namespace ECSCore
