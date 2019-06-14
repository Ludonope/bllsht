#ifndef BLLSHT_EGSE_INPUTREGISTERHOLDER_HPP
#define BLLSHT_EGSE_INPUTREGISTERHOLDER_HPP

#include "InputRegisterHolderConfig.hpp"
#include "bllsht/IReader.hpp"
#include <cstdint>

namespace bllsht::egse {
class InputRegisterHolder : public IReader {
public:
  InputRegisterHolder() = delete;
  InputRegisterHolder(std::uint16_t &valueHolder);

  InputRegisterHolder(std::uint16_t &valueHolder,
                      InputRegisterHolderConfig const &config);

  virtual std::uint16_t value() const;

private:
  std::string m_name;
  std::string m_type;
  std::uint16_t &m_valueHolder;
  double m_coef;
  double m_offset;
};
} // namespace bllsht::egse

#endif // BLLSHT_EGSE_INPUTREGISTERHOLDER_HPP