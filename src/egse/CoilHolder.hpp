#ifndef BLLSHT_EGSE_COILHOLDER_HPP
#define BLLSHT_EGSE_COILHOLDER_HPP

#include <string>

namespace bllsht::egse {
class CoilHolder {
public:
  CoilHolder(bool &valueHolder, std::string const &name)
      : m_valueHolder(valueHolder), m_name(name) {}

  bool read() const { return m_valueHolder; }
  std::string const &name() const { return m_name; }

private:
  bool m_valueHolder;
  std::string m_name;
};
} // namespace bllsht::egse

#endif // BLLSHT_EGSE_COILHOLDER_HPP