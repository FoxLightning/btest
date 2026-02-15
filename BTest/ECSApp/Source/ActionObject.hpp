// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once

#include <memory>
#include <string>

#include "ECSCore/Object.hpp"

#include "ECSApp/ECSAppAPI.hpp"

#include "PrintableInterface.hpp"

namespace ECSApp
{

class ActionObjectBase : public ECSCore::Object, public IPrintableInterface
{
  public:
    bool        IsVisible() const override = 0;
    std::string Print() const override     = 0;
    std::string GetName() const
    {
        return name;
    }

  protected:
    explicit ActionObjectBase(const std::weak_ptr<ECSCore::Entity>& inOwner, const ObjectName& inName)
        : Object(inOwner), name(inName.str)
    {
    }

  private:
    const std::string name;
};

} // namespace ECSApp
