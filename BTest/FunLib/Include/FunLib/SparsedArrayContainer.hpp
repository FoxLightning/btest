// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <vector>

#include "ContainerInterface.hpp"

namespace FunLib
{

template<typename tElement>
class TSparseArrayContainer : public IElementContainer<tElement>
{
  public:
    void Add(std::weak_ptr<tElement> element) override
    {
        if (freeSlotIndices.empty())
        {
            elementRegistry.emplace_back(element, true);
        }
        else
        {
            size_t freeIndex = freeSlotIndices.back();
            freeSlotIndices.pop_back();

            elementRegistry[freeIndex].element    = element;
            elementRegistry[freeIndex].isOccupied = true;
        }
        ++occupiedSlotsCount;
    }

    void EraseExpired() override
    {
        for (size_t i = 0; i < elementRegistry.size(); ++i)
        {
            if (auto& slot = elementRegistry[i]; slot.isOccupied && slot.element.expired())
            {
                slot.isOccupied = false;
                freeSlotIndices.push_back(i);
                --occupiedSlotsCount;
            }
        }
    }

    [[nodiscard]] std::weak_ptr<tElement> Find(const std::function<bool(std::weak_ptr<tElement>)>& predicate) override
    {
        return std::const_pointer_cast<tElement>(
            static_cast<const TSparseArrayContainer*>(this)->Find(predicate).lock());
    }

    [[nodiscard]] std::weak_ptr<const tElement> Find(
        const std::function<bool(std::weak_ptr<tElement>)>& predicate) const override
    {
        for (size_t i = 0; i < elementRegistry.size(); ++i)
        {
            if (const auto& slot = elementRegistry[i]; slot.isOccupied && predicate(slot.element))
            {
                return slot.element;
            }
        }
        return {};
    }

    void ForEach(const std::function<void(std::weak_ptr<tElement>)>& function) const override
    {
        for (size_t i = 0; i < elementRegistry.size(); ++i)
        {
            if (const auto& slot = elementRegistry[i]; slot.isOccupied)
            {
                function(slot.element);
            }
        }
    }

    [[nodiscard]] size_t Size() const override
    {
        return occupiedSlotsCount;
    }

  private:
    struct TSlot
    {
        std::weak_ptr<tElement> element;
        bool                    isOccupied{false};
    };
    std::vector<TSlot>  elementRegistry;
    std::vector<size_t> freeSlotIndices;
    size_t              occupiedSlotsCount{0};
};

} // namespace FunLib
