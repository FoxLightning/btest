// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once

#include <memory>

namespace ECSCore
{
class Entity;

class Object : public std::enable_shared_from_this<Object>
{
  public:
    Object()                         = delete;
    Object(const Object&)            = delete;
    Object& operator=(const Object&) = delete;
    Object(Object&&)                 = delete;
    Object& operator=(Object&&)      = delete;

    template<typename tObject, typename... tArgs>
    static std::shared_ptr<Object> CreateObject(const std::weak_ptr<Entity>& inOwner, tArgs&&... args)
    {
        auto createdObject = std::shared_ptr<tObject>(new tObject(inOwner, std::forward<tArgs>(args)...));
        createdObject->AttachObjectToEntity(createdObject);
        return createdObject;
    }

    virtual ~Object();

    [[nodiscard]] std::weak_ptr<Entity> GetOwner()
    {
        return owner;
    }

    [[nodiscard]] std::weak_ptr<Entity const> GetOwner() const
    {
        return owner;
    }

  protected:
    explicit Object(const std::weak_ptr<Entity>& inOwner) : owner(inOwner)
    {
    }

  private:
    void AttachObjectToEntity(const std::weak_ptr<Object>& object);
    void DetachObjectToEntity();

    const std::weak_ptr<Entity> owner;
};

} // namespace ECSCore
