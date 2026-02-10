// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <type_traits>
#include <vector>

#include "Object.hpp"

namespace ECSCore
{
class Entity;

class ObjectManager
{
  public:
    ObjectManager(const ObjectManager&)            = delete;
    ObjectManager(ObjectManager&&)                 = delete;
    ObjectManager& operator=(const ObjectManager&) = delete;
    ObjectManager& operator=(ObjectManager&&)      = delete;

    ObjectManager()          = default;
    virtual ~ObjectManager() = default;

    template<class tObjectType, class... tArgs>
    std::weak_ptr<tObjectType> CreateObject(tArgs... args);

    int32_t EraseObjectsIf(const std::function<bool(std::shared_ptr<Object>)>& predicate);

    [[nodiscard]] std::weak_ptr<Object>       GetObject(const std::function<bool(std::shared_ptr<Object>)>& predicate);
    [[nodiscard]] std::weak_ptr<const Object> GetObject(
        const std::function<bool(std::shared_ptr<Object>)>& predicate) const;

    void ForEachObject(const std::function<void(std::shared_ptr<Object>)>& function) const;

    [[nodiscard]] size_t GetObjectCount() const
    {
        return objectPool.size();
    }

  private:
    std::vector<std::shared_ptr<Object>> objectPool;
};

template<typename tObjectType, typename... tArgs>
std::weak_ptr<tObjectType> ObjectManager::CreateObject(tArgs... args)
{
    using tCleanObjectType = std::remove_cvref_t<tObjectType>;
    static_assert(std::is_base_of_v<Object, tCleanObjectType>);

    auto object = std::make_shared<tCleanObjectType>(args...);
    objectPool.emplace_back(object);
    return std::weak_ptr<tObjectType>(object);
}

} // namespace ECSCore
