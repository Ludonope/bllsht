#ifndef BLLSHT_EGSE_INPUTREGISTERGROUPCONFIG_HPP
#define BLLSHT_EGSE_INPUTREGISTERGROUPCONFIG_HPP

#include "InputRegisterHolderConfig.hpp"
#include "json/json.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace bllsht::egse {
struct InputRegisterGroupConfig {
  InputRegisterGroupConfig(nlohmann::json &json);

  std::uint16_t address;
  std::string type;
  std::vector<std::unique_ptr<InputRegisterHolderConfig>> sensors;
};
} // namespace bllsht::egse

#endif // BLLSHT_EGSE_INPUTREGISTERGROUPCONFIG_HPP