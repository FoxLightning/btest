// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once

#include <format>
#include <sstream>

#include "ActionObject.hpp"

namespace ECSApp
{

class MoveAction : public ActionObjectBase
{
  public:
    MoveAction(const std::weak_ptr<ECSCore::Entity>& inOwner, const ObjectName& objectName,
               std::string inTargetLocation)
        : ActionObjectBase(inOwner, objectName)
    {
        std::istringstream iss(std::move(inTargetLocation));
        iss >> x >> y;
    }

    bool IsVisible() const override
    {
        return true;
    }

    std::string Print() const override
    {
        return std::format("Move action: x={}, y={}", x, y);
    }

    static constexpr std::string::const_pointer GetTypeName()
    {
        return "MoveAction";
    }

  private:
    double x{0.};
    double y{0.};
};

} // namespace ECSApp
