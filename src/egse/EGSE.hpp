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
  EGSE(std::string const &configFile);
  ~EGSE();

  void loadConfig(std::string const &configFile);

  virtual std::string const& id() const { return m_id; }
  virtual std::vector<ICalibratedReader<std::uint16_t> const *> readSensors() const;
  virtual void broadcastData(IBroadcaster &broadcaster) const;
  void updateData();
  virtual void executeCommand(nlohmann::json &j);

protected:
  void actuate(nlohmann::json &payload);

  const std::string m_id = "egse";
  std::vector<egse::InputRegisterGroup> m_inputRegisterGroups;
  std::vector<egse::InputRegisterHolder> m_inputRegisterHolders;
  modbus m_modbusClient;
};
} // namespace bllsht

#endif // BLLSHT_EGSE_EGSE_HPP