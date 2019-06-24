#ifndef BLLSHT_EGSE_COILGROUP_HPP
#define BLLSHT_EGSE_COILGROUP_HPP

#include "CoilGroupConfig.hpp"
#include "modbuspp/modbus.h"
#include "json/json.hpp"
#include "CoilHolder.hpp"

namespace bllsht::egse {
class CoilGroup {
public:
  CoilGroup(modbus &modbusClient, nlohmann::json &json);
  CoilGroup(modbus &modbusClient, CoilGroupConfig const &config);

  CoilGroup(CoilGroup const &that);
  CoilGroup(CoilGroup &&that);
  ~CoilGroup();

  void updateData();
  std::vector<CoilHolder> const &holders() const { return m_holders; }
  bool set(std::string const &name, bool value);

protected:
  modbus &m_modbusClient;
  std::uint16_t m_address;
  std::uint16_t m_size;
  bool *m_values; // Cannot use std::vector<bool>, no data() method
  std::vector<CoilHolder> m_holders;
};
} // namespace bllsht::egse

#endif // BLLSHT_EGSE_COILGROUP_HPP