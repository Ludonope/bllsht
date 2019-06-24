#include "EGSE.hpp"
#include "json/json.hpp"
#include <exception>
#include <fstream>
#include <map>
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

  for (auto const &group : m_coilGroups) {
    for (auto const &holder : group.holders()) {
      m_coilHolders.push_back(holder);
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
  for (auto &el : j["coils"].items()) {
    m_coilGroups.emplace_back(m_modbusClient, el.value());
  }
}

std::vector<ICalibratedReader<std::uint16_t> const *>
EGSE::readSensors() const {
  std::vector<ICalibratedReader<std::uint16_t> const *> sensors;

  for (auto const &holder : m_inputRegisterHolders) {
    sensors.push_back(&holder);
  }

  return sensors;
}

void EGSE::broadcastData(IBroadcaster &broadcaster) const {
  for (auto const &holder : m_inputRegisterHolders) {
    double value = holder.read() * holder.coef() + holder.offset();
    auto packet = broadcast::make_packet("EGSE", holder.type(), holder.name(), value);
    broadcaster.broadcast(packet);
  }
  for (auto const &holder : m_coilHolders) {
    auto packet = broadcast::make_packet("EGSE", "relay", holder.name(), holder.read());
    broadcaster.broadcast(packet);
  }
}

void EGSE::updateData() {
  for (auto &group : m_inputRegisterGroups) {
    group.updateData();
  }
  for (auto &group : m_coilGroups) {
    group.updateData();
  }
}

void EGSE::executeCommand(nlohmann::json &j) {
  auto cmd = j["cmd"].get<std::string>();
  std::map<std::string, void (EGSE::*)(nlohmann::json &)> const commands = {
      {"actuate", &EGSE::actuate},
  };

  auto it = commands.find(cmd);
  if (it == commands.end()) {
    std::cout << "Unknown command '" << cmd << '\'' << std::endl;
    return;
  }

  (this->*it->second)(j["payload"]);
}

void EGSE::actuate(nlohmann::json &payload) {
  auto relay = payload["relay"].get<std::string>();
  auto state = payload["state"].get<bool>();
  std::cout << "Setting relay " << relay << " to " << state << std::endl;

  for (auto &group : m_coilGroups) {
    if (group.set(relay, state)) {
      break;
    }
  }
}

} // namespace bllsht