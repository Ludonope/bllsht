#ifndef BLLSHT_BROADCAST_GRPCBROADCASTER_HPP
#define BLLSHT_BROADCAST_GRPCBROADCASTER_HPP

#include "bllsht/IBroadcaster.hpp"
#include <iostream>

namespace bllsht::broadcast {
namespace {
template <typename T> class SpecializedGRPCBroadcaster {
public:
  virtual ~SpecializedGRPCBroadcaster() {}

  virtual void broadcast(std::string const &component, std::string const &type,
                         T const &value) {
    broadcast(component, type, value, "");
  }
  virtual void broadcast(std::string const &component, std::string const &type,
                         T const &value, std::string const &unit) {
    std::cout << '[' << component << "] " << type << ": " << value << unit
              << std::endl;
  }
};
} // namespace

class GRPCBroadcaster : public IBroadcaster {
public:
  virtual ~GRPCBroadcaster() {}

  virtual void broadcast(std::string const &component, std::string const &type,
                         double const &value) {
    broadcast(component, type, value, "");
  }
  virtual void broadcast(std::string const &component, std::string const &type,
                         double const &value, std::string const &unit) {
    _broadcast(component, type, value, unit);
  }

  virtual void broadcast(std::string const &component, std::string const &type,
                         bool const &value) {
    broadcast(component, type, value, "");
  }
  virtual void broadcast(std::string const &component, std::string const &type,
                         bool const &value, std::string const &unit) {
    _broadcast(component, type, value, unit);
  }

private:
  template <typename T>
  void _broadcast(std::string const &component, std::string const &type,
                  T const &value, std::string const &unit) {
    std::cout << '[' << component << "] " << type << ": " << value << unit
              << std::endl;
  }
};
} // namespace bllsht::broadcast

#endif // BLLSHT_BROADCAST_GRPCBROADCASTER_HPP