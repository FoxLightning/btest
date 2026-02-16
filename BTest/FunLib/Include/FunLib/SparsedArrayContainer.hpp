// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once

#include <cstddef>
#include <memory>

#include "ContainerInterface.hpp"

namespace FunLib
{

template<typename tElement>
class TSparsedArrayContainer : public  IElementContainer<tElement>
{
};

} // namespace FunLib
