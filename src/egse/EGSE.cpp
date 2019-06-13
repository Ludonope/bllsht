#include "EGSE.hpp"
#include <exception>
#include <string>

namespace bllsht {
EGSE::EGSE(std::string const &configFile)
    : m_inputRegisterGroups(), m_inputRegisterHolders(),
      m_modbusClient("127.0.0.1", 502) {

  // Connect to the modbus equipment
  m_modbusClient.modbus_set_slave_id(1);
  if (m_modbusClient.modbus_connect() == false) {
    throw std::runtime_error("Failed to connect modbus client");
  }

  // Setup register groups
  // TODO: load from config file
  m_inputRegisterGroups = std::vector<egse::InputRegisterGroup>{
      egse::InputRegisterGroup(m_modbusClient, 42, 12),
  };

  for (auto const &group : m_inputRegisterGroups) {
    for (auto const &holder : group.holders()) {
      m_inputRegisterHolders.push_back(holder);
    }
  }
}

EGSE::~EGSE() { m_modbusClient.modbus_close(); }

std::vector<IReader const *> EGSE::readSensors() const {
  std::vector<IReader const *> sensors;

  for (auto const &holder : m_inputRegisterHolders) {
    sensors.push_back(&holder);
  }

  return sensors;
}

void EGSE::updateData() {
  for (auto &group : m_inputRegisterGroups) {
    group.updateData();
  }
}

} // namespace bllsht