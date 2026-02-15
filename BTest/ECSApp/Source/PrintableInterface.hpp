// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once
#include <string>

namespace ECSApp
{

class IPrintableInterface
{
public:
    virtual ~IPrintableInterface() = default;
    virtual std::string Print() const = 0;
    virtual bool IsVisible() const = 0;
};

} // namespace ECSApp
