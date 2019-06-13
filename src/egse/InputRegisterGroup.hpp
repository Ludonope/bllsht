#ifndef SENSOR_INPUTREGISTERGROUP_HPP
#define SENSOR_INPUTREGISTERGROUP_HPP

#include "bllsht/IReader.hpp"
#include "modbuspp/modbus.h"
#include "InputRegisterHolder.hpp"
#include <cstdint>
#include <vector>

namespace bllsht::egse {
class InputRegisterGroup {
public:
  InputRegisterGroup(modbus &modbusClient, std::uint16_t address,
                     std::uint16_t size);

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

#endif // SENSOR_INPUTREGISTERGROUP_HPP