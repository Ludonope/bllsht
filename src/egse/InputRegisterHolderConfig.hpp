#ifndef BLLSHT_EGSE_INPUTREGISTERHOLDERCONFIG_HPP
#define BLLSHT_EGSE_INPUTREGISTERHOLDERCONFIG_HPP

#include "json/json.hpp"
#include <string>

namespace bllsht::egse {
struct InputRegisterHolderConfig {
  InputRegisterHolderConfig(nlohmann::json &json);

  std::string name;
  std::string type;
  double coef;
  double offset;
};
} // namespace bllsht::egse

#endif // BLLSHT_EGSE_INPUTREGISTERHOLDERCONFIG_HPP