#include "CoilGroupConfig.hpp"

namespace bllsht::egse {
CoilGroupConfig::CoilGroupConfig(nlohmann::json &json)
    : address(json["address"].get<std::uint16_t>()), coils() {
  for (auto &el : json["sensors"]) {
    if (el.is_null()) {
      this->coils.emplace_back(nullptr);
    } else {
      this->coils.push_back(
          std::make_unique<std::string>(el.get<std::string>()));
    }
  }
}
} // namespace bllsht::egse