#ifndef BLLSHT_BLLSHT_BROADCASTPACKET_HPP
#define BLLSHT_BLLSHT_BROADCASTPACKET_HPP
#include "json/json.hpp"

namespace bllsht::broadcast {
typedef nlohmann::json Packet;

template <class T>
Packet make_packet(std::string const &component, std::string const &type, std::string const &sensor,
                   T const &value, std::string const &unit) {
  Packet p;

  p["component"] = component;
  p["type"] = type;
  p["sensor"] = sensor;
  p["value"] = value;

  if (unit == "") {
    p["unit"] = nullptr;
  } else {
    p["unit"] = unit;
  }
  return p;
}

template <class T>
Packet make_packet(std::string const &component, std::string const &type, std::string const &sensor,
                   T const &value) {
  return make_packet(component, type, sensor, value, "");
}
} // namespace bllsht::broadcast

#endif // BLLSHT_BLLSHT_BROADCASTPACKET_HPP