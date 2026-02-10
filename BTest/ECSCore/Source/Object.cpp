// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include "ECSCore/Object.hpp"

#include <memory>
#include <string>
#include <utility>

#include "ECSCore/Entity.hpp"

namespace ECSCore
{

Object::Object(const std::weak_ptr<Entity>& inOwner)
{

}

Object::~Object()
{
}

void Object::AttachToEntity(const std::weak_ptr<Entity>& inOwner)
{
}

void Object::DetachFromEntity()
{
}

} // namespace ECSCore
