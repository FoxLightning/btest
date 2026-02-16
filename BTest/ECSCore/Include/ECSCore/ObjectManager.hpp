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

#include "FunLib/DynamicArrayContainer.hpp"
#include "FunLib/SparsedArrayContainer.hpp"

#include "Object.hpp"

namespace ECSCore
{
class Entity;
class Object;

class IObjectManager
{
  public:
    virtual ~IObjectManager()                                             = default;
    virtual bool TryAttachObjectToComponent(const std::weak_ptr<Object>& object) = 0;
    virtual void EraseExpiredWeakPointers()                               = 0;
};

template<typename tObjectType, typename tObjectContainer = FunLib::TDynamicArrayContainer<tObjectType>>
class TObjectManager : public IObjectManager
{
  public:
    TObjectManager(const TObjectManager&)            = delete;
    TObjectManager(TObjectManager&&)                 = delete;
    TObjectManager& operator=(const TObjectManager&) = delete;
    TObjectManager& operator=(TObjectManager&&)      = delete;

    TObjectManager()           = default;
    ~TObjectManager() override = default;

    virtual bool PostAttachObjectToComponent(const std::weak_ptr<Object>& object);

    bool TryAttachObjectToComponent(const std::weak_ptr<Object>& object) override;
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


/**
 * @brief Called after successfully attaching an object to the component, used to determine ownership.
 *
 * This virtual method is called after an object has been validated and added to the object registry.
 * The main goal is to determine ownership, classes which return true - are owners of the object and
 * stores shared reference.
 * Allowed only one owner for an entity
 *
 * @return bool True - manager is an owner of an entity and store shared ptr to it
 *              False - manager is not an owner of entity and store only weak ptr to it
 */
template<typename tObjectType, typename tObjectContainer>
bool TObjectManager<tObjectType, tObjectContainer>::PostAttachObjectToComponent(const std::weak_ptr<Object>& /* object */)
{
    return false;
}

template<typename tObjectType, typename tObjectContainer>
bool TObjectManager<tObjectType, tObjectContainer>::TryAttachObjectToComponent(const std::weak_ptr<Object>& object)
{
    if (const auto castedObject = std::dynamic_pointer_cast<tObjectType>(object.lock()))
    {
        objectRegistry.Add(castedObject);
        return PostAttachObjectToComponent(castedObject);
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
