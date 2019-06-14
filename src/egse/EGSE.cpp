#include "EGSE.hpp"
#include "json/json.hpp"
#include <exception>
#include <fstream>
#include <string>

namespace bllsht {
EGSE::EGSE(std::string const &configFile)
    : m_inputRegisterGroups(), m_inputRegisterHolders(),
      m_modbusClient("192.168.10.200", 502) {

  // Connect to the modbus equipment
  m_modbusClient.modbus_set_slave_id(1);
  if (m_modbusClient.modbus_connect() == false) {
    throw std::runtime_error("Failed to connect modbus client");
  }

  this->loadConfig(configFile);

  for (auto const &group : m_inputRegisterGroups) {
    for (auto const &holder : group.holders()) {
      m_inputRegisterHolders.push_back(holder);
    }
  }
}

EGSE::~EGSE() { m_modbusClient.modbus_close(); }

void EGSE::loadConfig(std::string const &configFile) {
  std::cout << "Loading config..." << std::endl;

  std::ifstream i(configFile);
  nlohmann::json j;

  if (i.fail()) {
    throw std::runtime_error("Failed to open config file");
  }

  i >> j;
  for (auto &el : j["input-registers"].items()) {
    m_inputRegisterGroups.emplace_back(m_modbusClient, el.value());
  }
}

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