// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#include <memory>
#include <string>

#include "ECSCore/Entity.hpp"
#include "ECSCore/EntityManager.hpp"
#include "ECSCore/Object.hpp"
#include "ECSCore/ObjectManager.hpp"

class ConcreteObjectManagerA : public ECSCore::ObjectManager
{
};

class ConcreteObjectA final : public ECSCore::Object
{
  public:
    ConcreteObjectA() = delete;
    ConcreteObjectA(const std::string& inName, const std::weak_ptr<ECSCore::Entity>& inOwner) : Object(inName, inOwner) {}

    ECSCore::EObjectType GetObjectType() const override;
};

ECSCore::EObjectType ConcreteObjectA::GetObjectType() const
{
    return ECSCore::EObjectType::ConcreteObjectA;
}

template<>
struct ECSCore::TObjectManagerTrait<ConcreteObjectA>
{
    using ManagerType = ConcreteObjectManagerA;
};


int main()
{
    return 0;
}
