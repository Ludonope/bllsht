#include "InputRegisterHolder.hpp"

namespace bllsht::egse {
InputRegisterHolder::InputRegisterHolder(std::uint16_t &valueHolder)
    : m_valueHolder(valueHolder) {}

std::uint16_t InputRegisterHolder::value() const { return m_valueHolder; }
} // namespace bllsht::egse