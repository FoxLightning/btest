// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include "ECSCore/Object.hpp"

#include <memory>

#include "ECSCore/Entity.hpp"

namespace ECSCore
{

Object::~Object()
{
    DetachObjectToEntity();
}

void Object::AttachObjectToEntity(const std::weak_ptr<Object>& object)
{
    owner.lock()->AttachObjectToEntity(object);
}

void Object::DetachObjectToEntity()
{
    if (const auto sharedOwner = owner.lock())
    {
        sharedOwner->DetachObjectFromEntity();
    }
}

} // namespace ECSCore
