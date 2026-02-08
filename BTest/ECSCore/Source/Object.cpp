// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include "ECSCore/Object.hpp"

#include <memory>
#include <string>
#include <utility>

namespace ECSCore
{

Object::Object(std::string inName, const std::weak_ptr<Entity>& inOwner) : name(std::move(inName)), owner(inOwner)
{
}

} // namespace ECSCore
