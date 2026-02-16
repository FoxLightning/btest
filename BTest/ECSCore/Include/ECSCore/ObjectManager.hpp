// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once

#include <algorithm>
#include <concepts>
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

namespace FunLib
{

template<typename tElement>
class IObjectContainer
{
  public:
    virtual ~IObjectContainer() = default;

    virtual void                          Add(std::weak_ptr<tElement> object)                                       = 0;
    virtual void                          EraseExpired()                                                            = 0;
    virtual std::weak_ptr<tElement>       Find(const std::function<bool(std::weak_ptr<tElement>)>& predicate)       = 0;
    virtual std::weak_ptr<const tElement> Find(const std::function<bool(std::weak_ptr<tElement>)>& predicate) const = 0;
    virtual void                 ForEach(const std::function<void(std::weak_ptr<tElement>)>& function) const        = 0;
    [[nodiscard]] virtual size_t Size() const                                                                       = 0;
};

class TDynamicArrayContainer : public IObjectContainer<Object>
{
  public:
    void Add(std::weak_ptr<Object> object) override
    {
        objectRegistry.emplace_back(object);
    }

    void EraseExpired() override
    {
        std::erase_if(objectRegistry, [](const std::weak_ptr<Object>& weakObject) { return weakObject.expired(); });
    }
    std::weak_ptr<Object> Find(const std::function<bool(std::weak_ptr<Object>)>& predicate) override
    {
        const auto iterator = std::ranges::find_if(objectRegistry, predicate);
        return iterator != objectRegistry.end() ? std::weak_ptr<Object>{*iterator} : std::weak_ptr<Object>{};
    }
    std::weak_ptr<const Object> Find(const std::function<bool(std::weak_ptr<Object>)>& predicate) const override
    {
        const auto iterator = std::ranges::find_if(objectRegistry, predicate);
        return iterator != objectRegistry.end() ? std::weak_ptr<const Object>{*iterator}
                                                : std::weak_ptr<const Object>{};
    }
    void ForEach(const std::function<void(std::weak_ptr<Object>)>& function) const override
    {
        std::ranges::for_each(objectRegistry, function);
    }
    [[nodiscard]] size_t Size() const override
    {
        return objectRegistry.size();
    }

  private:
    std::vector<std::weak_ptr<Object>> objectRegistry;
};

} // namespace FunLib

class IObjectManager
{
  public:
    virtual ~IObjectManager()                                             = default;
    virtual bool TryAttachObjectToComponent(std::weak_ptr<Object> object) = 0;
    virtual void EraseExpiredWeakPointers()                               = 0;
};

template<typename tObjectType, typename tObjectContainer = FunLib::TDynamicArrayContainer>
class TObjectManager : public IObjectManager
{
  public:
    TObjectManager(const TObjectManager&)            = delete;
    TObjectManager(TObjectManager&&)                 = delete;
    TObjectManager& operator=(const TObjectManager&) = delete;
    TObjectManager& operator=(TObjectManager&&)      = delete;

    TObjectManager()           = default;
    ~TObjectManager() override = default;

    virtual bool PostAttachObjectToComponent(std::weak_ptr<Object> object);

    bool TryAttachObjectToComponent(std::weak_ptr<Object> object) override;
    void EraseExpiredWeakPointers() override;

    [[nodiscard]] std::weak_ptr<Object>       GetObject(const std::function<bool(std::weak_ptr<Object>)>& predicate);
    [[nodiscard]] std::weak_ptr<const Object> GetObject(
        const std::function<bool(std::weak_ptr<Object>)>& predicate) const;

    void ForEachObject(const std::function<void(std::weak_ptr<Object>)>& function) const;

    [[nodiscard]] size_t GetObjectCount() const
    {
        return objectRegistry.Size() - expiredCount;
    }

  private:
    static constexpr int32_t GExpiredLimit{100};
    int32_t                  expiredCount{0};
    tObjectContainer         objectRegistry;
};

template<typename tObjectType, typename tObjectContainer>
bool TObjectManager<tObjectType, tObjectContainer>::PostAttachObjectToComponent(std::weak_ptr<Object> /* object */)
{
    return false;
}

template<typename tObjectType, typename tObjectContainer>
bool TObjectManager<tObjectType, tObjectContainer>::TryAttachObjectToComponent(std::weak_ptr<Object> object)
{
    if (std::dynamic_pointer_cast<tObjectType>(object.lock()))
    {
        objectRegistry.Add(object);
        return PostAttachObjectToComponent(object);
    }
    return false;
}

template<typename tObjectType, typename tObjectContainer>
void TObjectManager<tObjectType, tObjectContainer>::EraseExpiredWeakPointers()
{
    if (expiredCount > GExpiredLimit)
    {
        objectRegistry.EraseExpired();
        expiredCount = 0;
        return;
    }
    ++expiredCount;
}

template<typename tObjectType, typename tObjectContainer>
std::weak_ptr<Object> TObjectManager<tObjectType, tObjectContainer>::GetObject(
    const std::function<bool(std::weak_ptr<Object>)>& predicate)
{
    const std::weak_ptr constWeak = std::as_const(*this).GetObject(predicate);

    if (const std::shared_ptr sharedWeak = constWeak.lock())
    {
        return std::weak_ptr{std::const_pointer_cast<Object>(sharedWeak)};
    }

    return {};
}

template<typename tObjectType, typename tObjectContainer>
std::weak_ptr<const Object> TObjectManager<tObjectType, tObjectContainer>::GetObject(
    const std::function<bool(std::weak_ptr<Object>)>& predicate) const
{
    return objectRegistry.Find(predicate);
}

template<typename tObjectType, typename tObjectContainer>
void TObjectManager<tObjectType, tObjectContainer>::ForEachObject(
    const std::function<void(std::weak_ptr<Object>)>& function) const
{
    objectRegistry.ForEach(function);
}

} // namespace ECSCore
