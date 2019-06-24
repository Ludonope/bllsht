#include "CoilGroup.hpp"

namespace bllsht::egse {
CoilGroup::CoilGroup(modbus &modbusClient, nlohmann::json &json)
    : CoilGroup(modbusClient, CoilGroupConfig(json)) {}

CoilGroup::CoilGroup(modbus &modbusClient, CoilGroupConfig const &conf)
    : m_modbusClient(modbusClient), m_address(conf.address),
      m_size(static_cast<std::uint16_t>(conf.coils.size())),
      m_values(new bool[conf.coils.size()]), m_holders() {
  for (std::size_t i = 0; i < conf.coils.size(); i++) {
    auto const &name = conf.coils[i];
    if (name) {
      m_holders.emplace_back(m_values[i], *name);
    }
  }
}

CoilGroup::CoilGroup(CoilGroup const &that)
    : m_modbusClient(that.m_modbusClient), m_address(that.m_address),
      m_size(that.m_size), m_values(new bool[that.m_size]),
      m_holders(that.m_holders) {
  for (std::size_t i = 0; i < m_size; ++i) {
    m_values[i] = that.m_values[i];
  }
}

CoilGroup::CoilGroup(CoilGroup &&that)
    : m_modbusClient(that.m_modbusClient), m_address(that.m_address),
      m_size(that.m_size), m_values(that.m_values),
      m_holders(std::move(that.m_holders)) {
  that.m_values = nullptr;
}

CoilGroup::~CoilGroup() {
  if (m_values) {
    delete[] m_values;
  }
}

void CoilGroup::updateData() {
  m_modbusClient.modbus_read_coils(m_address, m_size, m_values);
}

bool CoilGroup::set(std::string const &name, bool value) {
  for (std::size_t i = 0; i < m_holders.size(); i++) {
    if (name == m_holders[i].name()) {
      m_modbusClient.modbus_write_coils(m_address + i, 1, &value);
      return true;
    }
  }
  return false;
}
} // namespace bllsht::egse