#ifndef BLLSHT_BLLSHT_ICALIBRATEDREADER_HPP
#define BLLSHT_BLLSHT_ICALIBRATEDREADER_HPP

#include "IReader.hpp"
#include <cstdint>
#include <string>

namespace bllsht {
  template<class T>
class ICalibratedReader : public IReader<T> {
public:
  virtual ~ICalibratedReader() {}

  virtual double coef() const = 0;
  virtual double offset() const = 0;
};
} // namespace bllsht

#endif // BLLSHT_BLLSHT_ICALIBRATEDREADER_HPP