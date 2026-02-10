// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once

#include <memory>

namespace ECSCore
{
class Entity;

class Object
{
  public:
    Object()                         = delete;
    Object(const Object&)            = delete;
    Object& operator=(const Object&) = delete;
    Object(Object&&)                 = delete;
    Object& operator=(Object&&)      = delete;

    explicit Object(const std::weak_ptr<Entity>& inOwner);

    virtual ~Object();

    [[nodiscard]] std::weak_ptr<Entity> GetOwner()
    {
        return owner;
    }

    [[nodiscard]] std::weak_ptr<Entity const> GetOwner() const
    {
        return owner;
    }

  private:
    void AttachToEntity(const std::weak_ptr<Entity>& inOwner);
    void DetachFromEntity();

    const std::weak_ptr<Entity> owner;
};

} // namespace ECSCore
