#ifndef SENSOR_IREADER_HPP
#define SENSOR_IREADER_HPP

#include <cstdint>

namespace bllsht {
class IReader {
public:
  virtual ~IReader() {}

  // typedef void (*CallbackType)(std::uint16_t);

  // virtual void onData(CallbackType callback) = 0;
  virtual std::uint16_t value() const = 0;
};
} // namespace bllsht

#endif // SENSOR_IREADER_HPP