#include "InputRegisterGroupConfig.hpp"

namespace bllsht::egse {
InputRegisterGroupConfig::InputRegisterGroupConfig(nlohmann::json &json)
    : address(json["address"].get<std::uint16_t>()), type(""), sensors() {
  if (json.contains("type")) {
    this->type = json["type"].get<std::string>();
  }

  for (auto &el : json["sensors"]) {
    if (el.is_null()) {
      this->sensors.emplace_back(nullptr);
    } else {
      this->sensors.push_back(std::make_unique<InputRegisterHolderConfig>(el));
    }
  }
}
} // namespace bllsht::egse