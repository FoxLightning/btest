// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once

#include <cstddef>
#include <memory>
#include <ranges>
#include <vector>

#include "ContainerInterface.hpp"

namespace FunLib
{

/*
 * Adapter for std::vector
 */
template<typename tElement>
class TDynamicArrayContainer : public IElementContainer<tElement>
{
  public:
    void Add(std::weak_ptr<tElement> element) override
    {
        elementRegistry.emplace_back(element);
    }

    void EraseExpired() override
    {
        std::erase_if(elementRegistry,
                      [](const std::weak_ptr<tElement>& weakElement) { return weakElement.expired(); });
    }
    [[nodiscard]] std::weak_ptr<tElement> Find(const std::function<bool(std::weak_ptr<tElement>)>& predicate) override
    {
        return std::const_pointer_cast<tElement>(static_cast<const TDynamicArrayContainer*>(this)->Find(predicate).lock());
    }
    [[nodiscard]] std::weak_ptr<const tElement> Find(
        const std::function<bool(std::weak_ptr<tElement>)>& predicate) const override
    {
        const auto iterator = std::ranges::find_if(elementRegistry, predicate);
        return iterator != elementRegistry.end() ? std::weak_ptr<const tElement>{*iterator}
                                                 : std::weak_ptr<const tElement>{};
    }
    void ForEach(const std::function<void(std::weak_ptr<tElement>)>& function) const override
    {
        std::ranges::for_each(elementRegistry, function);
    }
    [[nodiscard]] size_t Size() const override
    {
        return elementRegistry.size();
    }

  private:
    std::vector<std::weak_ptr<tElement>> elementRegistry;
};

} // namespace FunLib
