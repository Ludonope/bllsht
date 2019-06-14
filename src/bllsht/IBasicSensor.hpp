#ifndef BLLSHT_BLLSHT_BASICSENSOR_HPP
#define BLLSHT_BLLSHT_BASICSENSOR_HPP

#include <cstdint>
#include <string>

namespace bllsht {
class IBasicSensor {
public:
  virtual ~IBasicSensor() {}

  virtual std::string const &name() const = 0;
  virtual std::string const &type() const = 0;
};
} // namespace bllsht

#endif // BLLSHT_BLLSHT_BASICSENSOR_HPP