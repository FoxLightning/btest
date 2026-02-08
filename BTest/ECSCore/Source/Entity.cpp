// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include "ECSCore/Entity.hpp"
#include <string>
#include <utility>

namespace ECSCore
{
Entity::Entity(std::string inName) : name(std::move(inName))
{
}

Entity::~Entity()
{
}

std::string Entity::GetName() const
{
    return name;
}
} // namespace ECSCore
