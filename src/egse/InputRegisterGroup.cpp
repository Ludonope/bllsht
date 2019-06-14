#include "InputRegisterGroup.hpp"

namespace bllsht::egse {
InputRegisterGroup::InputRegisterGroup(modbus &modbusClient,
                                       std::uint16_t address,
                                       std::uint16_t size)
    : m_modbusClient(modbusClient), m_address(address), m_size(size),
      m_values(size), m_holders() {
  for (auto &val : m_values) {
    m_holders.emplace_back(val);
  }
}

InputRegisterGroup::InputRegisterGroup(modbus &modbusClient,
                                       nlohmann::json &json)
    : InputRegisterGroup(modbusClient, InputRegisterGroupConfig(json)) {}

InputRegisterGroup::InputRegisterGroup(modbus &modbusClient,
                                       InputRegisterGroupConfig const &conf)
    : m_modbusClient(modbusClient), m_address(conf.address),
      m_size(static_cast<std::uint16_t>(conf.sensors.size())),
      m_values(conf.sensors.size()), m_holders() {
  for (std::size_t i = 0; i < conf.sensors.size(); i++) {
    auto const &sensor = conf.sensors[i];
    if (sensor) {
      m_holders.emplace_back(m_values[i], *sensor);
    }
  }
}

void InputRegisterGroup::updateData() {
  m_modbusClient.modbus_read_input_registers(m_address, m_size,
                                             m_values.data());
}

std::vector<InputRegisterHolder> const &InputRegisterGroup::holders() const {
  return m_holders;
}

} // namespace bllsht::egse