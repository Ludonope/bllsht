#ifndef BLLSHT_EGSE_INPUTREGISTERHOLDER_HPP
#define BLLSHT_EGSE_INPUTREGISTERHOLDER_HPP

#include "bllsht/IReader.hpp"
#include <cstdint>

namespace bllsht::egse {
class InputRegisterHolder : public IReader {
public:
  InputRegisterHolder() = delete;
  InputRegisterHolder(std::uint16_t &valueHolder);

  virtual std::uint16_t value() const;

private:
  std::uint16_t &m_valueHolder;
};
} // namespace bllsht::egse

#endif // BLLSHT_EGSE_INPUTREGISTERHOLDER_HPP