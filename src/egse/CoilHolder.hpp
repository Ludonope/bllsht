#ifndef BLLSHT_EGSE_COILHOLDER_HPP
#define BLLSHT_EGSE_COILHOLDER_HPP

#include <string>

namespace bllsht::egse {
class CoilRegisterHolder {
public:
  CoilRegisterHolder(bool &valueHolder, std::string const &name);

  bool read() const { return m_valueHolder; }
  std::string const &name() const { return m_name; }

private:
  std::string m_name;
  bool m_valueHolder;
};
} // namespace bllsht::egse

#endif // BLLSHT_EGSE_COILHOLDER_HPP