#ifndef BLLSHT_EGSE_COILGROUPCONFIG_HPP
#define BLLSHT_EGSE_COILGROUPCONFIG_HPP

#include "json/json.hpp"
#include <cstdint>

namespace bllsht::egse {
struct CoilGroupConfig {
  CoilGroupConfig(nlohmann::json &json);

  std::uint16_t address;
  std::vector<std::unique_ptr<std::string>> coils;
};
} // namespace bllsht::egse

#endif // BLLSHT_EGSE_COILGROUPCONFIG_HPP