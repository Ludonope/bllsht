#ifndef BLLSHT_BLLSHT_IEQUIPMENT_HPP
#define BLLSHT_BLLSHT_IEQUIPMENT_HPP

#include "IBroadcaster.hpp"
#include "json/json.hpp"
#include <string>
#include <vector>

namespace bllsht {
class IEquipment {
public:
  virtual ~IEquipment(){};

  virtual std::string const &id() const = 0;
  virtual void broadcastData(IBroadcaster &broadcaster) const = 0;
  virtual void executeCommand(nlohmann::json &j) = 0;
};
} // namespace bllsht

#endif // BLLSHT_BLLSHT_IEQUIPMENT_HPP