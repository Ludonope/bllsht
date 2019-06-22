#ifndef BLLSHT_EGSE_INPUTREGISTERGROUP_HPP
#define BLLSHT_EGSE_INPUTREGISTERGROUP_HPP

#include "bllsht/IReader.hpp"
#include "modbuspp/modbus.h"
#include "InputRegisterHolder.hpp"
#include "InputRegisterGroupConfig.hpp"
#include "json/json.hpp"
#include <cstdint>
#include <vector>

namespace bllsht::egse {
class InputRegisterGroup {
public:
  InputRegisterGroup(modbus &modbusClient, nlohmann::json &json);
  InputRegisterGroup(modbus &modbusClient, InputRegisterGroupConfig const &config);

  // virtual std::vector<std::uint16_t> const &value();
  void updateData();
  std::vector<InputRegisterHolder> const &holders() const;
  // std::vector<>
  // virtual void onData(IReader::CallbackType callback);

protected:
  modbus &m_modbusClient;
  std::uint16_t m_address;
  std::uint16_t m_size;
  std::vector<std::uint16_t> m_values;
  std::vector<InputRegisterHolder> m_holders;
};
} // namespace bllsht::egse

#endif // BLLSHT_EGSE_INPUTREGISTERGROUP_HPP