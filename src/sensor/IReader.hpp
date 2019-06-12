#ifndef SENSOR_IREADER_HPP
# define SENSOR_IREADER_HPP

# include <cstdint>

template<class T>
class IReader {
  virtual ~IReader() {}

  virtual T value() = 0;
};

#endif // SENSOR_IREADER_HPP