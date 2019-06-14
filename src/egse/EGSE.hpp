#ifndef BLLSHT_EGSE_EGSE_HPP
#define BLLSHT_EGSE_EGSE_HPP

#include "InputRegisterGroup.hpp"
#include "bllsht/IEquipment.hpp"
#include "bllsht/IReader.hpp"
#include "modbuspp/modbus.h"
#include <string>
#include <vector>

namespace bllsht {
class EGSE final : public IEquipment {
public:
  EGSE() = default;
  EGSE(std::string const &configFile);
  ~EGSE();

  void loadConfig(std::string const &configFile);

  virtual std::string const& name() const { return "EGSE"; }
  virtual std::vector<IReader const *> readSensors() const;
  void updateData();

protected:
  std::vector<egse::InputRegisterGroup> m_inputRegisterGroups;
  std::vector<egse::InputRegisterHolder> m_inputRegisterHolders;
  modbus m_modbusClient;
};
} // namespace bllsht

#endif // BLLSHT_EGSE_EGSE_HPP