// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once

#include <string_view>

namespace CLIApp
{

class CommandBase
{
public:
    virtual std::string_view GetName() const = 0;
};

} // namespace CLIApp
