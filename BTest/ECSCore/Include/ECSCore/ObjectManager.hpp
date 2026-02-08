// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>

#include "Object.hpp"

namespace ECSCore
{
class Entity;

class ObjectManager
{
  public:
    ObjectManager()                                = delete;
    ObjectManager(const ObjectManager&)            = delete;
    ObjectManager(ObjectManager&&)                 = delete;
    ObjectManager& operator=(const ObjectManager&) = delete;
    ObjectManager& operator=(ObjectManager&&)      = delete;

    explicit ObjectManager(std::shared_ptr<Entity> inOwner) : owner(std::move(inOwner))
    {
    }
    virtual ~ObjectManager() = default;

    template<typename ObjectType>
    std::weak_ptr<ObjectType> CreateObject(const std::string& inName);
    bool                      DeleteObject(const std::string& inName);

    [[nodiscard]] std::weak_ptr<Object>       GetObject(const std::string& inName);
    [[nodiscard]] std::weak_ptr<const Object> GetObject(const std::string& inName) const;

    void ForEachObject(const std::function<void(std::weak_ptr<Object>)>& function) const;

    [[nodiscard]] size_t GetObjectCount() const
    {
        return objectPool.size();
    }

  private:
    const std::shared_ptr<Entity>                            owner;
    std::unordered_map<std::string, std::shared_ptr<Object>> objectPool;
};

template<typename ObjectType>
std::weak_ptr<ObjectType> ObjectManager::CreateObject(const std::string& inName)
{
    using CleanObjectType = std::remove_cvref_t<ObjectType>;
    static_assert(std::is_base_of_v<Object, CleanObjectType>);

    auto [pair, isInserted] = objectPool.emplace(inName, nullptr);

    if (isInserted)
    {
        pair->second = std::make_shared<CleanObjectType>(inName, owner);
    }
    return pair->second;
}

} // namespace ECSCore
