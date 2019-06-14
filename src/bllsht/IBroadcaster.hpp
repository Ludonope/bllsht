#ifndef BLLSHT_BLLSHT_IBROADCASTER_HPP
#define BLLSHT_BLLSHT_IBROADCASTER_HPP

#include <string>

namespace bllsht {
template <typename T> class ISpecializedBroadcaster {
public:
  virtual ~ISpecializedBroadcaster(){};

  virtual void broadcast(std::string const &component, std::string const &type,
                         T const &value) = 0;
  virtual void broadcast(std::string const &component, std::string const &type,
                         T const &value, std::string const &unit) = 0;
};

class IBroadcaster : public ISpecializedBroadcaster<double>,
                     ISpecializedBroadcaster<bool> {
public:
  virtual ~IBroadcaster(){};
  using ISpecializedBroadcaster<double>::broadcast;
  using ISpecializedBroadcaster<bool>::broadcast;
};
} // namespace bllsht

#endif // BLLSHT_BLLSHT_IBROADCASTER_HPP