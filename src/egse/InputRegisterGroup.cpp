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

void InputRegisterGroup::updateData() {
  m_modbusClient.modbus_read_input_registers(m_address, m_size,
                                             m_values.data());
}

std::vector<InputRegisterHolder> const &InputRegisterGroup::holders() const {
  return m_holders;
}

} // namespace bllsht::egse