#ifndef BLLSHT_BLLSHT_IEQUIPMENT_HPP
#define BLLSHT_BLLSHT_IEQUIPMENT_HPP

#include "IReader.hpp"
#include <string>
#include <vector>

namespace bllsht {
class IEquipment {
public:
  virtual ~IEquipment(){};

  virtual std::string const &name() const = 0;
  virtual std::vector<IReader const *> readSensors() const = 0;
};
} // namespace bllsht

#endif // BLLSHT_BLLSHT_IEQUIPMENT_HPP