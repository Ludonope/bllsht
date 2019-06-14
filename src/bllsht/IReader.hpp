#ifndef BLLSHT_BLLSHT_IREADER_HPP
#define BLLSHT_BLLSHT_IREADER_HPP

#include "IBasicSensor.hpp"
#include <cstdint>
#include <string>

namespace bllsht {
  template<class T>
class IReader : public IBasicSensor {
public:
  virtual ~IReader() {}

  virtual T read() const = 0;
};
} // namespace bllsht

#endif // BLLSHT_BLLSHT_IREADER_HPP