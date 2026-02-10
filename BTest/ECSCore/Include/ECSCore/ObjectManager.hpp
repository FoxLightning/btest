// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once

#include <algorithm>
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
class Object;

class IObjectManager
{
  public:
    virtual ~IObjectManager()                    = default;
};

template<typename tObjectType>
class TObjectManager : public IObjectManager
{
  public:
    TObjectManager(const TObjectManager&)            = delete;
    TObjectManager(TObjectManager&&)                 = delete;
    TObjectManager& operator=(const TObjectManager&) = delete;
    TObjectManager& operator=(TObjectManager&&)      = delete;

    TObjectManager()           = default;
    ~TObjectManager() override = default;

    template<class... tArgs>
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

template<typename tObjectType>
template<class... tArgs>
std::weak_ptr<tObjectType> TObjectManager<tObjectType>::CreateObject(tArgs... args)
{
    using tCleanObjectType = std::remove_cvref_t<tObjectType>;
    static_assert(std::is_base_of_v<Object, tCleanObjectType>);

    auto object = std::make_shared<tCleanObjectType>(args...);
    objectPool.emplace_back(object);
    return std::weak_ptr<tObjectType>(object);
}

template<typename tObjectType>
int32_t TObjectManager<tObjectType>::EraseObjectsIf(const std::function<bool(std::shared_ptr<Object>)>& predicate)
{
    return static_cast<int32_t>(std::erase_if(objectPool, predicate));
}

template<typename tObjectType>
std::weak_ptr<Object> TObjectManager<tObjectType>::GetObject(
    const std::function<bool(std::shared_ptr<Object>)>& predicate)
{
    const std::weak_ptr constWeak = std::as_const(*this).GetObject(predicate);

    if (const std::shared_ptr sharedWeak = constWeak.lock())
    {
        return std::weak_ptr{std::const_pointer_cast<Object>(sharedWeak)};
    }

    return {};
}

template<typename tObjectType>
std::weak_ptr<const Object> TObjectManager<tObjectType>::GetObject(
    const std::function<bool(std::shared_ptr<Object>)>& predicate) const
{
    const auto iterator = std::ranges::find_if(objectPool, predicate);
    return iterator != objectPool.end() ? std::weak_ptr<const Object>{*iterator} : std::weak_ptr<const Object>{};
}

template<typename tObjectType>
void TObjectManager<tObjectType>::ForEachObject(const std::function<void(std::shared_ptr<Object>)>& function) const
{
    std::ranges::for_each(objectPool, function);
}

} // namespace ECSCore
