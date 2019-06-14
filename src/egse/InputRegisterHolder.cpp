#include "InputRegisterHolder.hpp"

namespace bllsht::egse {
InputRegisterHolder::InputRegisterHolder(std::uint16_t &valueHolder,
                                         InputRegisterHolderConfig const &conf)
    : m_name(conf.name), m_type(conf.type), m_valueHolder(valueHolder),
      m_coef(conf.coef), m_offset(conf.offset) {}
} // namespace bllsht::egse