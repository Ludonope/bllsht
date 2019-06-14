#ifndef BLLSHT_EGSE_INPUTREGISTERHOLDER_HPP
#define BLLSHT_EGSE_INPUTREGISTERHOLDER_HPP

#include "InputRegisterHolderConfig.hpp"
#include "bllsht/IReader.hpp"
#include <cstdint>

namespace bllsht::egse {
class  InputRegisterHolder final : public IReader {
public:
  InputRegisterHolder() = delete;
  InputRegisterHolder(std::uint16_t &valueHolder,
                      InputRegisterHolderConfig const &config);

  virtual std::uint16_t value() const { return m_valueHolder; }
  virtual std::string const &name() const { return m_name; }
  virtual std::string const &type() const { return m_type; }
  virtual double coef() const { return m_coef; }
  virtual double offset() const { return m_offset; }

private:
  std::string m_name;
  std::string m_type;
  std::uint16_t &m_valueHolder;
  double m_coef;
  double m_offset;
};
} // namespace bllsht::egse

#endif // BLLSHT_EGSE_INPUTREGISTERHOLDER_HPP