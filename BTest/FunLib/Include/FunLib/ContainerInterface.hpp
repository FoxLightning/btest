// Proprietary & Confidential — All Rights Reserved — Copyright (c) 2026 Bohdan Lysychenko — See LICENSE.

#pragma once

#include <cstddef>
#include <functional>
#include <memory>

template<typename tElement>
class IElementContainer
{
  public:
    virtual ~IElementContainer() = default;

    virtual void                          Add(std::weak_ptr<tElement> element)                                      = 0;
    virtual void                          EraseExpired()                                                            = 0;
    virtual std::weak_ptr<tElement>       Find(const std::function<bool(std::weak_ptr<tElement>)>& predicate)       = 0;
    virtual std::weak_ptr<const tElement> Find(const std::function<bool(std::weak_ptr<tElement>)>& predicate) const = 0;
    virtual void                 ForEach(const std::function<void(std::weak_ptr<tElement>)>& function) const        = 0;
    [[nodiscard]] virtual size_t Size() const                                                                       = 0;
};
