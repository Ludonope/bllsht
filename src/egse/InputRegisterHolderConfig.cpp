#include "InputRegisterHolderConfig.hpp"

namespace bllsht::egse {
InputRegisterHolderConfig::InputRegisterHolderConfig(nlohmann::json &json)
    : name(json["name"].get<std::string>()), type(""), coef(1), offset(0) {
  if (json.contains("type")) {
    this->type = json["type"].get<std::string>();
  }

  if (json.contains("coef")) {
    this->coef = json["coef"].get<double>();
  }

  if (json.contains("offset")) {
    this->coef = json["offset"].get<double>();
  }
}
} // namespace bllsht::egse