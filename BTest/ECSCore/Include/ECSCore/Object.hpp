// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <utility>

namespace ECSCore
{
class ObjectManager;
class Entity;
class Object;

template<typename T>
struct TObjectManagerTrait;

template<>
struct TObjectManagerTrait<Object>
{
    using ManagerType = ObjectManager;
};

enum class EObjectType : uint8_t
{
    Null = 0,
    ConcreteObjectA,
    ConcreteObjectB,
    ConcreteObjectC,
    Count
};

constexpr std::array<std::string_view, std::to_underlying(EObjectType::Count)> GObjectTypeNames{
    "Null", "ConcreteObjectA", "ConcreteObjectB", "ConcreteObjectC"};

constexpr std::string_view GetObjectName(const EObjectType type)
{
    return GObjectTypeNames[std::to_underlying(type)];
}

EObjectType GetObjectName(const std::string& name);

/**
 * Base class for Objects.
 * Abstract.
 * To implement a new derived class:
 * 1. Register a type in EObjectType enum.
 * 2. Register a type name in GObjectTypeNames with the corresponding index.
 * 3. Register TObjectManagerTrait
 */
class Object
{
  public:
    Object() = delete;
    explicit Object(std::string inName, std::weak_ptr<Entity> inOwner)
        : name(std::move(inName)), owner(std::move(inOwner))
    {
    }
    virtual ~Object() = default;

    [[nodiscard]] std::string GetName() const
    {
        return name;
    }
    [[nodiscard]] std::weak_ptr<Entity> GetOwner() const
    {
        return owner;
    }
    [[nodiscard]] virtual EObjectType GetObjectType() const = 0;

    using ManagerType = TObjectManagerTrait<Object>::ManagerType;

  private:
    const std::string           name;
    const std::weak_ptr<Entity> owner;
};

} // namespace ECSCore
