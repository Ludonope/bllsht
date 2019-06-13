#ifndef BLLSHT_BLLSHT_IEQUIPMENT_HPP
#define BLLSHT_BLLSHT_IEQUIPMENT_HPP

#include <vector>
#include "IReader.hpp"

namespace bllsht {
class IEquipment {
public:
  virtual ~IEquipment(){};

  virtual std::vector<IReader const *> readSensors() const = 0;
};
} // namespace bllsht

#endif // BLLSHT_BLLSHT_IEQUIPMENT_HPP