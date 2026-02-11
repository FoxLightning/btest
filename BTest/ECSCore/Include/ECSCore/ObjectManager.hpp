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
    virtual ~IObjectManager()                                             = default;
    // TODO do something with return bool or remove it
    virtual bool TryAttachObjectToComponent(std::weak_ptr<Object> object) = 0;
    virtual void EraseExpiredWeakPointers()                               = 0;
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

    bool TryAttachObjectToComponent(std::weak_ptr<Object> object) override;
    // TODO fix performance
    void EraseExpiredWeakPointers() override;

    [[nodiscard]] std::weak_ptr<Object>       GetObject(const std::function<bool(std::weak_ptr<Object>)>& predicate);
    [[nodiscard]] std::weak_ptr<const Object> GetObject(
        const std::function<bool(std::weak_ptr<Object>)>& predicate) const;

    void ForEachObject(const std::function<void(std::weak_ptr<Object>)>& function) const;

    [[nodiscard]] size_t GetObjectCount() const
    {
        return objectRegistry.size();
    }

  private:
    std::vector<std::weak_ptr<Object>> objectRegistry;
};

template<typename tObjectType>
bool TObjectManager<tObjectType>::TryAttachObjectToComponent(std::weak_ptr<Object> object)
{
    if (std::dynamic_pointer_cast<tObjectType>(object.lock()))
    {
        objectRegistry.emplace_back(object);
        return true;
    }
    return false;
}

template<typename tObjectType>
void TObjectManager<tObjectType>::EraseExpiredWeakPointers()
{
    std::erase_if(objectRegistry,
                           [](const std::weak_ptr<Object>& weakObject) { return weakObject.expired(); });
}

template<typename tObjectType>
std::weak_ptr<Object> TObjectManager<tObjectType>::GetObject(
    const std::function<bool(std::weak_ptr<Object>)>& predicate)
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
    const std::function<bool(std::weak_ptr<Object>)>& predicate) const
{
    const auto iterator = std::ranges::find_if(objectRegistry, predicate);
    return iterator != objectRegistry.end() ? std::weak_ptr<const Object>{*iterator} : std::weak_ptr<const Object>{};
}

template<typename tObjectType>
void TObjectManager<tObjectType>::ForEachObject(const std::function<void(std::weak_ptr<Object>)>& function) const
{
    std::ranges::for_each(objectRegistry, function);
}

} // namespace ECSCore
